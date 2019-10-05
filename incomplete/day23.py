from collections import defaultdict
with open('input') as f: s = [l.strip() for l in f.readlines()] #list of lines with the trailing whitespace at the end and start removed
pos = defaultdict(lambda:0)
nbot_max = (0,0,0)
for l in s:
    x,y,z = map(int,l[5:-10].strip()[:-2].split(','))
    pos[x,y,z] = int(l[-8:])
    if pos[x,y,z] > pos[nbot_max]: nbot_max = x,y,z
def solve2():
    xl,yl,zl = [[c[i] for c in pos] for i in range(3)]
    dist = 1
    while dist < max(xl)-min(xl): dist<<=1
    while dist:
        target_c = 0
        best = best_val = None
        for x in xrange(min(xl), max(xl)+1, dist):  #loop through cube holding all bots, at intervals of dist
            for y in xrange(min(yl), max(yl)+1, dist):
                for z in xrange(min(zl), max(zl)+1, dist):
                    n = sum([bool((sum(map(lambda v: abs(v[0]-v[1]), zip((x,y,z),c)))-pos[c])/dist <= 0) for c in pos])
                    if n > target_c or (n == target_c and sum(map(abs,(x,y,z))) < best_val):
                        target_c = n        #set new largest number of bots in range
                        best = (x,y,z)      #set new best coords
                        best_val = sum(map(abs,best)) #and best answer
        xl, yl, zl = [[best[i]-dist,best[i]+dist] for i in range(3)]
        dist>>=1
    return best_val
print sum([bool(sum(map(lambda v: abs(v[0]-v[1]),zip(k,nbot_max))) <= pos[nbot_max]) for k in pos]) #part 1
print solve2()
