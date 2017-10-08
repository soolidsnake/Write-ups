k = open('output.png', 'w')
f = open('secret_encrypted.png', 'r')


def xor(data):
    decoded = ""
    for i in range(0, len(data)):
            decoded += chr(ord(data[i]) ^ 0xff )

    return decoded

data = f.read()
k.write(xor(data))