from operator import * #get function version of normal operators
with open('input') as f: s = [l.strip() for l in f.readlines()] #list of lines with the trailing whitespace at the end and start removed

OP_LIST = [gt,eq] + [iadd, add, mul, and_, or_, gt, eq]*2   #The ordering of the operations originally used for mapping
#In the puzzle's terms: gtir, eqir, (set,add,mul,ban,bor,gtr,eqr)*(r,i) 
map_dict = dict([i[::-1] for i in enumerate(['gtir', 'eqir','setr','addr','mulr','banr','borr','gtrr','eqrr','seti','addi','muli','bani','bori','gtri','eqri'])])
TYPES=[('i','r')]*2                                         #the TYPES list is necessary to turn the operators into a generic() function
for t in ['r','i']: TYPES += [(t,'z')] + [('r',t)]*6        #initalise TYPES without needing to type everything manually
OPS = len(OP_LIST)          #number of operators

def generic(v,c,op,t):  #ideally this should be done with default values, instead of nasty tuples of V and t
    global regist
    V = [1,0]           #[1,0] instead of [0,1]. Alternatively, the for loop below could contain a check for 'z' for set*
    for i in [1,0]:
        if t[i] == 'r': V[i] = regist[v[i]] #use register value if necessary
        if t[i] == 'i': V[i] = v[i]         #just use the number if supposed to
    regist[c] = op(V[0],V[1])       #call op() on the two values
#BEGIN PART 1
ins_ind = int(s[0][4:])
instr = []
for l in [a.split() for a in s[1:]]:
    tmp = [l[0]]
    tmp += map(int,l[1:])
    instr.append(tmp)

ins_ptr = 0
regist = [0,0,0,0,0,0]
numbers = set()
prev = 0
from time import time
t = time()
while ins_ptr < len(s):
    regist[ins_ind] = ins_ptr
    o,a,b,c = instr[ins_ptr]
    generic((a,b),c,OP_LIST[map_dict[o]], TYPES[map_dict[o]])
    if ins_ptr == 28:
        if not numbers: print "first: %d" % regist[5]
        if regist[5] in numbers: break
        numbers.add(regist[5])
        prev = regist[5]
    ins_ptr = regist[ins_ind]
    ins_ptr += 1
print "val: %d" % prev
