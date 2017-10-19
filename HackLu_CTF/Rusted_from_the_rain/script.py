"""

	Author : BITAM Salim
	GIT : https://github.com/soolidsnake/

"""


from z3 import *


s = Solver()

f0=BitVec('f0', 64)
f1=BitVec('f1', 64)
f2=BitVec('f2', 64)
f3=BitVec('f3', 64)
f4=BitVec('f4', 64)
f5=BitVec('f5', 64)
f6=BitVec('f6', 64)
f7=BitVec('f7', 64)
f8=BitVec('f8', 64)
f9=BitVec('f9', 64)
f10=BitVec('f10', 64)
f11=BitVec('f11', 64)
f12=BitVec('f12', 64)
f13=BitVec('f13', 64)
f14=BitVec('f14', 64)
f15=BitVec('f15', 64)
f16=BitVec('f16', 64)
f17=BitVec('f17', 64)
f18=BitVec('f18', 64)
f19=BitVec('f19', 64)
f20=BitVec('f20', 64)
f21=BitVec('f21', 64)
f22=BitVec('f22', 64)
f23=BitVec('f23', 64)
f24=BitVec('f24', 64)
f25=BitVec('f25', 64)
f26=BitVec('f26', 64)
f27=BitVec('f27', 64)



s.add(f0 < 127)
s.add(f1 < 127)
s.add(f2 < 127)
s.add(f3 < 127)
s.add(f4 < 127)
s.add(f5 < 127)
s.add(f6 < 127)
s.add(f7 < 127)
s.add(f8 < 127)
s.add(f9 < 127)
s.add(f10 < 127)
s.add(f11 < 127)
s.add(f12 < 127)
s.add(f13 < 127)
s.add(f14 < 127)
s.add(f15 < 127)
s.add(f16 < 127)
s.add(f17 < 127)
s.add(f18 < 127)
s.add(f19 < 127)
s.add(f20 < 127)
s.add(f21 < 127)
s.add(f22 < 127)
s.add(f23 < 127)
s.add(f24 < 127)
s.add(f25 < 127)
s.add(f26 < 127)
s.add(f27 < 127)


s.add(f0 > 48)
s.add(f1 > 48)
s.add(f2 > 48)
s.add(f3 > 48)
s.add(f4 > 48)
s.add(f5 > 48)
s.add(f6 > 48)
s.add(f7 > 48)
s.add(f8 > 48)
s.add(f9 > 48)
s.add(f10 > 48)
s.add(f11 > 48)
s.add(f12 > 48)
s.add(f13 > 48)
s.add(f14 > 48)
s.add(f15 > 48)
s.add(f16 > 48)
s.add(f17 > 48)
s.add(f18 > 48)
s.add(f19 > 48)
s.add(f20 > 48)
s.add(f21 > 48)
s.add(f22 > 48)
s.add(f23 > 48)
s.add(f24 > 48)
s.add(f25 > 48)
s.add(f26 > 48)
s.add(f27 > 48)




s.add(f9  == f16)
s.add(f9  == f21)
s.add(f13 == f14)
s.add(f18 == f19)
s.add(f5  == f26)
s.add(f23 == f7)
s.add(f8  == f22)


s.add(f27  == 2 + f4 )
s.add(f0 == 7 + 63)
s.add(f1 == 0xd + 63)
s.add(f2 == 2 + 63)
s.add(f3 == 8 + 63)


s.add(f4 == ord('{'))# When i found that the first 4 chars are 'FLAG' I knew that the fifth gonna be an '{'


s.add(f21 <= 0x60)

s.add(f18 + f14 == 0xD1)
s.add(f14 == 7 + f18)


s.add(f10 == f15)
s.add(~f24 & f17 == 0)
s.add(f17 == 115)
s.add((~(f10 ^ 0x73) == -1 ))
s.add( (2 * f25) % f24 == 2 )
s.add(( (f23 + f25) ) & 0xff == 35 +  99 * (( ( 83 * ( (f23 + f25) &0xff ) )  & 0x6000) >> 13  ) )#recheck


s.add(3 * f11 + 2 * f12 + f20 == 640 )
s.add(f6  == 6 + 35 * ( ( 235 * f6 & 0xE000 ) >> 13)) # recheck
s.add( ((2 * f6) % f8) & 0xff == f14 )


# LOOP checks
summ = f0 + f1 + f2 + f3 + f4 + f5 + f6
summ_summ = f0 + f0 + f1 + f0 + f1 + f2 + f0 + f1 + f2 + f3 + f0 + f1 + f2 + f3 + f4 + f0 + f1 + f2 + f3 + f4 + f5 + f0 + f1 + f2 + f3 + f4 + f5 + f6
s.add( (summ_summ%0xff | ( (( summ%0xff ) << 8)  )) == 0x7FED )


summ = f7 + f8 + f9 + f10 + f11 + f12 + f13 
summ_summ = f7 + f7 + f8 + f7 + f8 + f9 + f7 + f8 + f9 + f10 + f7 + f8 + f9 + f10 + f11 + f7 + f8 + f9 + f10 + f11 + f12 + f7 + f8 + f9 + f10 + f11 + f12 + f13
s.add( (summ_summ%0xff | ( (( summ%0xff ) << 8)  )) == 0xFB11 )


summ = f14 + f15 + f16 + f17 + f18 + f19 + f20  
summ_summ = f14 + f14 + f15 + f14 + f15 + f16 + f14 + f15 + f16 + f17 + f14 + f15 + f16 + f17 + f18 + f14 + f15 + f16 + f17 + f18 + f19 + f14 + f15 + f16 + f17 + f18 + f19 + f20
s.add( (summ_summ%0xff | ( (( summ%0xff ) << 8)  )) == 0xeabe )


summ = f21 + f22 + f23 + f24 + f25 + f26 + f27 
summ_summ = f21 + f21 + f22 + f21 + f22 + f23 + f21 + f22 + f23 + f24 + f21 + f22 + f23 + f24 + f25 + f21 + f22 + f23 + f24 + f25 + f26 + f21 + f22 + f23 + f24 + f25 + f26 + f27
s.add( (summ_summ%0xff | ( (( summ%0xff ) << 8)  )) == 0x2631 )




if s.check() == sat:
	mod = s.model()
	solus = [mod[f0],mod[f1],mod[f2],mod[f3],mod[f4],mod[f5],mod[f6],mod[f7],mod[f8],mod[f9],mod[f10],mod[f11],mod[f12],mod[f13],mod[f14],mod[f15],mod[f16],mod[f17],mod[f18],mod[f19],mod[f20],mod[f21],mod[f22],mod[f23],mod[f24],mod[f25],mod[f26],mod[f27]]

	print ''.join([chr(int(str(i))) for i in solus])


