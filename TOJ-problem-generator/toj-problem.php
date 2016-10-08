<?php
function getstdinline(){
	$text=fgets(STDIN);
	$text=substr($text,0,-2);
	return $text;
}
function getfoldername($text){
	if($text[0]=="\"")$text=substr($text,1,-1);
	if($text[strlen($text)-1]=="\\")$text=substr($text,0,-1);
	return $text;
}
echo "Output folder >";
$folder = trim(fgets(STDIN));
mkdir($folder);
chdir($folder);
mkdir("http");
mkdir("res");
mkdir("res/testdata");
echo "Problem file >";
$input = trim(fgets(STDIN));
copy($input, "http/cont.".pathinfo($input, PATHINFO_EXTENSION));
echo "timelimit >";
$timelimit = (int)trim(fgets(STDIN));
echo "memlimit >";
$memlimit = (int)trim(fgets(STDIN));
echo "testdata folder >";
$testdatafolder = trim(fgets(STDIN));
$filecheck = array();
$filelist = scandir($testdatafolder);
foreach ($filelist as $file) {
	$filename = pathinfo($file);
	if (is_numeric($filename["filename"])) {
		$filecheck[$filename["filename"]][$filename["extension"]] = true;
	}
}
$indexlist = array();
foreach ($filecheck as $key => $value) {
	if (isset($value["in"]) && isset($value["out"])) {
		copy($testdatafolder."/".$key.".in", "res/testdata/".(int)$key.".in");
		copy($testdatafolder."/".$key.".out", "res/testdata/".(int)$key.".out");
		echo "find ".$key.".in and ".$key.".out . copid.\n";
		$indexlist[(int)$key] = (int)$key;
	} else if(isset($value["in"])) {
		echo "find ".$key.".in but ".$key.".out is missing. ignored\n";
	} else if(isset($value["out"])) {
		echo "find ".$key.".out but ".$key.".in is missing. ignored\n";
	}
}
var_dump($indexlist);
asort($indexlist);
var_dump($indexlist);
$conf = new stdClass;
$conf->timelimit = $timelimit;
$conf->memlimit = $memlimit;
$conf->compile = "g++";
$conf->score = "rate";
$conf->check = "diff";
$conf->test = array();
while (true) {
	$templist = array();
	echo "input testdata index (format:1-4,5,6,7-9)(empty string to exit)\n";
	echo "not used: ".implode(",", $indexlist)."\n";
	echo ">";
	$input = trim(fgets(STDIN));
	if ($input == "") break;
	foreach (explode(",", $input) as $temp) {
		if (preg_match("/(\d+)-(\d+)/", $input, $match)) {
			for ($i = (int)$match[1]; $i <= (int)$match[2]; $i++) {
				$templist[] = $i;
				unset($indexlist[$i]);
			}
		} else {
			$templist[] = (int)$temp;
			unset($indexlist[(int)$temp]);
		}
	}
	echo "input testdata ".implode(",",$templist)." score >";
	$score = (int)trim(fgets(STDIN));
	$conf->test[] = array("data"=>$templist, "weight"=>$score);
}
file_put_contents("conf.json", json_encode($conf, JSON_PRETTY_PRINT));
echo "Done!\n";
?>
