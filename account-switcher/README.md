# account-switcher
快速切換帳號

1. 清除TOJ上的所有cookie
2. 重新整理並登入第一個帳號
3. 把名為id的cookie的HttpOnly屬性取消掉
4. 按下swap cookie的書籤小程式(此時應該會看到有id和temp_id兩個cookie，id的值為空，temp_id的值為原來id的值)
5. 登入第二個帳號
6. 再次把名為id的cookie的HttpOnly屬性取消掉
7. 恭喜完成! 此後可以按swapTOJ快速切換兩個帳號了
PS. 清除及修改cookie建議可用:http://www.editthiscookie.com/
