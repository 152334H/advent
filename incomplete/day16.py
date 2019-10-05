from operator import * #get function version of normal operators
with open('input') as f: s = [l.strip() for l in f.readlines()] #list of lines with the trailing whitespace at the end and start removed
for i in range(len(s)): #seek to end of part 1
    if not s[i] and not s[i+1] and not s[i+2]: break
first, second = s[:i], s[i+3:]
opcodes = dict([(x,[]) for x in range(16)])                 #stores the possible operations that opcode X could refer to
OP_LIST = [gt,eq] + [iadd, add, mul, and_, or_, gt, eq]*2   #The ordering of the operations originally used for mapping
#In the puzzle's terms: gtir, eqir, (set,add,mul,ban,bor,gtr,eqr)*(r,i) 
TYPES=[('i','r')]*2                                         #the TYPES list is necessary to turn the operators into a generic() function
for t in ['r','i']: TYPES += [(t,'z')] + [('r',t)]*6        #initalise TYPES without needing to type everything manually
OPS = len(OP_LIST)          #number of operators

def generic(v,c,op,t):  #ideally this should be done with default values, instead of nasty tuples of V and t
    V = [1,0]           #[1,0] instead of [0,1]. Alternatively, the for loop below could contain a check for 'z' for set*
    for i in [1,0]:
        if t[i] == 'r': V[i] = regist[v[i]] #use register value if necessary
        if t[i] == 'i': V[i] = v[i]         #just use the number if supposed to
    regist[c] = op(V[0],V[1])       #call op() on the two values
def operator(o): #returns a standard function with inputs a, b, and c, given operator o. A leftover piece of design.
    return lambda a,b,c: generic((a,b),c,OP_LIST[o],TYPES[o])
#BEGIN PART 1
gt_3_c = 0      #number of samples behaving like 3+ opcodes
for i in range(0,len(first),4):         #loop over input 1
    bef     = map(int, first[i][9:-1].split(', '))      #Before: bef
    o,a,b,c = map(int,first[i+1].split())           #o a b c
    aft     = map(int, first[i+2][9:-1].split(', '))    #After:  aft
    curr_codes = []      #list of possible codes for the current sample
    for op_n in range(OPS): #for all operators
        regist = bef[:]     #deep copy
        generic((a,b),c,OP_LIST[op_n],TYPES[op_n])  #call the generic function on the operator
        if regist == aft:   #if operator shows same output as aft:
            if op_n not in opcodes[o]: opcodes[o].append(op_n)      #append the operator for further usage
            if op_n not in curr_codes: curr_codes.append(op_n) #do the same for the current sample
    if len(curr_codes) > 2: gt_3_c += 1          #add to the 3+ count if necessary
print gt_3_c        #show answer to part 1
#END PART 1, BEGIN PART 2
opcode_points_to = dict([(x,-1) for x in range(16)])    #map of the opcodes to their expected ones
while [ls for ls in opcodes.values() if len(ls)>1]:     #while an opcode maps to several operators
    for k in opcodes.keys():    #for opcodes
        if len(opcodes[k]) > 1:     #if opcode maps to several
            for code in opcodes[k]:     #for the possible operations
                if code in [v[0] for v in opcodes.values() if len(v) == 1]: del opcodes[k][opcodes[k].index(code)] #remove the operation if it's mapping is already certain
for k in opcodes: opcodes[k] = opcodes[k][0]    #this significantly increases pypy runtime, but the whole script is already fast
regist = [0,0,0,0]  #(re)set register
for l in second:    #for the lines in the second input
    o,a,b,c = map(int,l.split())    #set the values
    operator(opcodes[o])(a,b,c)     #and execute
print regist[0]     #print the contents of register 0 after execution
