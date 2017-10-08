Lets open the given png with xxd and compare it with another png,

Encrypted image header : ![alt text](https://github.com/soolidsnake/Write-ups/blob/master/Kaspersky_CTF/Security%20home%20cameras/encrypted_image_header.png)

random image header :  ![alt text](https://github.com/soolidsnake/Write-ups/blob/master/Kaspersky_CTF/Security%20home%20cameras/random_image_header.png)


if we xor the first byte of each picture we get 0xFF, lets xor the whole encrypted png with 0xFF with [This script](https://github.com/soolidsnake/Write-ups/blob/master/Kaspersky_CTF/Security%20home%20cameras/script.py).
