LNMAX=1<<8
d = {}                                      #dictionary of reproductional notes
offset = -10                                #offset is used to reduce memory footprint by ignoring empty pots
with open('input') as f:
    s = [l.strip() for l in f.readlines()]  #list of lines with the trailing whitespace at the end and start removed
    init = s[0].split()[2]                  #get the pots at generation 0
    for l in s[2:]: d[l[:5]] = l[9:]

array = ['.' for x in range(-offset)]       #array is an array of the pots
oldarr = array                              #oldarr is used later for pattern checking
for c in init: array.append(c)              #set the plants into pots
while len(array) != LNMAX: array.append('.')#lengthen array[] to a standard length

def loop(array, rang, offset):
    global oldarr
    for time in rang:
        newa = ['.' for x in range(LNMAX)]
        for p in range(3,LNMAX-3): newa[p] = d[''.join(array[p-2:p+3])]
        if '#' not in newa[:60]:                #if the first 50+ pots are all empty
            offset += 50                        #set the offset forward so that
            newa = newa[50:]+['.']*50           #we can shift the empty space in the array away
        if time % 10 == 0:                      #for every 10 generations,
            if oldarr[:-10] == newa[10:]: return sum(50000000000-time+i+offset for i in range(len(array)) if array[i] == '#')  #once a pattern is found, return the total sum
            oldarr = newa
        array = newa
    return sum(i+offset for i in range(len(array)) if array[i] == '#')  #print the total sum for part 1
print "sum after 20  generations: %d" % loop(array, range(20), offset)
print "sum after 50B generations: %d" % loop(array, xrange(1000), offset)
