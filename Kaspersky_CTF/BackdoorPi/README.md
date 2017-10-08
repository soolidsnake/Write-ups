


Checking the passwd file I found out that there is a user called 'b4ckd00r\_us3r', after that I looked up for crontab files and found a file named 'b4ckd00r\_us3r'


after opening b4ckd00r_us3r I found out that there is a task that lunches /bin/back

command 'file' reveals that /bin/back is a python compiled files, lets use uncompyle6 for this task, I got the fellowing code :

![alt text](https://github.com/soolidsnake/Write-ups/blob/master/Kaspersky_CTF/BackdoorPi/cron_b4ckd00r_us3r.png)

looks like the program asks for a username and pincode then compute 'username:pincode' with sha256, lets use the username found previously
I wrote a small python [Script](https://github.com/soolidsnake/Write-ups/blob/master/Kaspersky_CTF/BackdoorPi/script.py) to brute force the pin
