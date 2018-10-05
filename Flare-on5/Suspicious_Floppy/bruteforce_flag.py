import string
import itertools
from pwn import *

post_flag = '@flare-on.com'
flag_len = 30
summ = 0
length_var = 0x8400

hashes = [0xfc7f, 0xf30f, 0xf361, 0xf151,0xf886,0xf3d1,0xdb57,0xd9d5,0xe26e,0xf8cd,0xf969,0xd90c,0xf821,0xf181,0xf85f]

def pre_calc(a, b):
	return ((ord(a) - 0x20) + ((ord(b) - 0x20) << 7)&0xffff)

def get_sum(a):
	s = 0
	for i in a:
		s += ord(i)

A = pre_calc('o', 'm')^(33*14)
summ = hashes[14] - length_var - A

flag = ''

for i in xrange(flag_len/2):
	for combo in itertools.product(string.printable, repeat=2):
		A = pre_calc(combo[0], combo[1])^(33*i)
		B = summ + length_var
		
		if A + B == hashes[i]:
			flag += combo[0] + combo[1]

log.success('flag=> %s',flag)