#!/usr/bin/env python3

import argparse
import json
import os
import subprocess
import stat
import tempfile


def build_checker(prob_dir):
    check_path = os.path.abspath(os.path.join(prob_dir, 'res', 'check'))
    build_path = os.path.abspath(os.path.join(check_path, 'build'))
    subprocess.check_call([build_path], cwd=check_path)
    return os.path.abspath(os.path.join(check_path, 'check'))


def runner(prog, fdmap, envs):
    pid = os.fork()
    if pid != 0:
        return pid

    for (target_fd, src) in fdmap.items():
        if hasattr(src, 'fileno'):
            src = src.fileno()

        os.dup2(src, target_fd)

    os.execve(prog, [prog], envs)
    os._exit(0)


def run_test(prob_dir, test_id, test_prog, check_prog, metadata):
    print('Testing {}:'.format(test_id))

    test_dir = os.path.join(prob_dir, 'res', 'testdata')
    in_path = os.path.join(test_dir, '{}.in'.format(test_id))
    ans_path = os.path.join(test_dir, '{}.out'.format(test_id))
    out_file = tempfile.NamedTemporaryFile()
    in_pipe = os.pipe()
    out_pipe = os.pipe()
    
    redir_test = metadata['redir_test']
    test_fdmap = {}
    if redir_test['testin'] != -1:
        test_fdmap[redir_test['testin']] = open(in_path, 'rb')
    if redir_test['testout'] != -1:
        test_fdmap[redir_test['testout']] = out_file
    if redir_test['pipein'] != -1:
        test_fdmap[redir_test['pipein']] = in_pipe[0]
    if redir_test['pipeout'] != -1:
        test_fdmap[redir_test['pipeout']] = out_pipe[1]

    redir_check = metadata['redir_check']
    check_fdmap = {}
    if redir_check['testin'] != -1:
        check_fdmap[redir_check['testin']] = open(in_path, 'rb')
    if redir_check['ansin'] != -1:
        check_fdmap[redir_check['ansin']] = open(ans_path, 'rb')
    if redir_check['pipein'] != -1:
        check_fdmap[redir_check['pipein']] = in_pipe[1]
    if redir_check['pipeout'] != -1:
        check_fdmap[redir_check['pipeout']] = out_pipe[0]

    output_path = out_file.name
    verdict_path = os.path.join(os.getcwd(), 'verdict.txt')
    check_pid = runner(check_prog, check_fdmap, {'OUTPUT': output_path, 'VERDICT': verdict_path})
    test_pid = runner(test_prog, test_fdmap, {})

    print('output path: {}, verdict path: {}'.format(output_path, verdict_path))
    print('test_prog exit {}'.format(os.waitpid(test_pid, 0)))
    print('check_prog exit {}'.format(os.waitpid(check_pid, 0)))
    out_file.close()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('prob_dir', type=str, help='problem dir')
    parser.add_argument('test_prog', type=str, help='test program')
    args = parser.parse_args()

    prob_dir = args.prob_dir
    test_prog = os.path.abspath(args.test_prog)
    conf_json = os.path.join(prob_dir, 'conf.json')
    conf = json.load(open(conf_json, 'r'))
    assert conf['check'] == 'ioredir'

    tests = []
    for bundle in conf['test']:
        tests += bundle['data']

    check_prog = build_checker(prob_dir)
    for test_id in tests:
        run_test(prob_dir, test_id, test_prog, check_prog, conf['metadata'])

if __name__ == '__main__':
    main()
