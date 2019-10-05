from operator import * #get function version of normal operators
with open('input') as f: s = [l.strip() for l in f.readlines()] #list of lines with the trailing whitespace at the end and start removed

opcodes = dict([(x,[]) for x in range(16)])                 #stores the possible operations that opcode X could refer to
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
def operator(o): #returns a standard function with inputs a, b, and c, given operator o. A leftover piece of design.
    return lambda a,b,c: generic((a,b),c,OP_LIST[o],TYPES[o])
#BEGIN PART 1
ins_ind = 0
instr = []
for l in s:
    if l[0] == '#': ins_ind = int(l[4:])
    else: instr.append(l.split())
ins_ptr = 0
regist = [1,0,0,0,0,0]
while ins_ptr < len(instr):
    regist[ins_ind] = ins_ptr
    a,b,c = map(int,instr[ins_ptr][1:])
    #print "ip=%d %r %s" % (ins_ptr, regist, instr[ins_ptr]),
    operator(map_dict[instr[ins_ptr][0]])(a,b,c)
    #print "%r" % regist
    if ins_ptr == 35 or ins_ptr == 27: print regist[3]
    if ins_ptr == 35: exit() #remove this line to bruteforce day 19
    ins_ptr = regist[ins_ind]
    ins_ptr += 1
print "val: %d" % regist[0]
