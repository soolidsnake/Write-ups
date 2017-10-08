


Checking the passwd file I found out that there is a user called 'b4ckd00r\_us3r', after that I looked up for crontab files and found a file named 'b4ckd00r\_us3r'


after opening b4ckd00r_us3r I found out that there is a task that lunches /bin/back
lets check what kind of file /bin/back is :

it's a python compiled files, lets use uncompyle6 for this task, I got the fellowing code :

looks like the program asks for a username and pincode then compute 'username:pincode' with sha256, lets use the username found previously
I wrote a small python script to brute force the pin