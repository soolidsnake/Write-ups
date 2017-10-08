out = open('output.png', 'w')
in = open('secret_encrypted.png', 'r')


def xor(data):
    decoded = ""
    for i in range(0, len(data)):
            decoded += chr(ord(data[i]) ^ 0xff )

    return decoded

data = in.read()
out.write(xor(data))

in.close()
out.close()
