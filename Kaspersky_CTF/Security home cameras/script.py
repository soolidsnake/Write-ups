output = open('output.png', 'w')
input = open('secret_encrypted.png', 'r')


def xor(data):
    decoded = ""
    for i in range(0, len(data)):
            decoded += chr(ord(data[i]) ^ 0xff )

    return decoded

data = input.read()
k.write(xor(data))

input.close()
output.close()
