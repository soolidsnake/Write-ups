import string
import itertools
import struct
'''
        Hack Dat Kiwi 2017 Polyglot Exploit
        @author Bitam Salim (github.com/soolidsnake)
'''

def float_to_hex(f):
    return hex(struct.unpack('<I', struct.pack('<f', f))[0])
def hex_to_float(f):
    return struct.unpack('>f', struct.pack('>l', f))[0]
def somethingsomethingdarkside(x):
        #https://en.wikipedia.org/wiki/Fast_inverse_square_root
        i = int(float_to_hex(x), 16)
        h = 0.5*x;
        i = 0x5f3759df - (i>>1) 
        x = hex_to_float(i) #check this
        x = (x * (1.5 - (h * x * x)))
        return x

def main(arg):
        arg[88] = 0
        s = ''.join([i for i in arg[83:88]])
        x = int(s)/5
        x >>= 1

        y  = int(1/somethingsomethingdarkside(float(x)))
        y2 = int(1/somethingsomethingdarkside(float(x+1)))

        return y == 36 and y2 != y;

def split_by_lenght(ch):
        x = 12
        return [int(ch[i: i + x]) for i in range(0, len(ch), x)]

def calcul(ch):
        t=0
        for x in list(ch):
                t=(t+ord(x))*256
        return t

def sub(result, x, y):
        if x < y:
                return result[x : y]
        else:
                return result[x -1 : x + y - 2] + 'X' + result[x + y -1 : y + x -1 + 1 ] 

def nastify(ch, word_len):
        result = ''
        for i, c in enumerate(ch):
                if  (i+1) % word_len != 0:
                        result += chr(ord(c) + 0x20)
        return result

hardcoded = 'TZOPBTPBIBTUEIBTISIBTCCIBTCFIBTNSIBTDRCSCATSETBTRAPBPESNPSUESITFOARTTTGTSBOAPOOOWTDIATWMNBOAFUYRDNIBTNANIOBTRNITIIHTEISABIITIIETEIMBAGINAOHGILSDMOT'


# Everything above is just copied from the original code

with open('/usr/share/dict/words') as f:
    words = f.readlines()
words = [x.strip() for x in words] 

for word in words:

        ch =  'KIWI' + word.upper() + hardcoded
        ch = sub(ch, 0, 8) + sub(ch, 10, 9) + sub(ch, 9, 100)
        ch += '\n'
        ch = nastify(ch, len(word)+4)
        cpt = calcul(ch)
        cpt_list = split_by_lenght(str(cpt))
        cpt_list.sort()
        arg =  ''.join([str(i) for i in cpt_list])
        arg = list(arg)

        g = ord(arg[121])
        f = ord(arg[122])
        a = ord(arg[86])
        b = ord(arg[85])
        
        tmp = g 
        g = b
        b = tmp

        arg[121] = chr(g); # Exchange b and g && f and a
        arg[85]  = chr(b)
        arg[122] = chr(a)
        arg[86]  = chr(f)

        if main(arg):
                print 'KIWI'+word.upper()       
                



        
