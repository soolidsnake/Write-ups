import itertools
import hashlib

numbers = '0123456789'
user = 'b4ckd00r_us3r'
pin = ''
for pincode in itertools.product(numbers, repeat=8):
	pin = ''
	for i in pincode:
		pin.append
	val = '{}:{}'.format(user, pin)
	key = hashlib.sha256(val).hexdigest()
	if key == '34c05015de48ef10309963543b4a347b5d3d20bbe2ed462cf226b1cc8fff222e':
		print 'Congr4ts, you found the b@ckd00r. The fl4g is simply : {}:{}'.format(user, pin)
		exit()