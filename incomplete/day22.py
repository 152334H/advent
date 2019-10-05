from collections import defaultdict
def print_map():
    global type_map
    try:
        xmax = max([c[0] for c in type_map])
        ymax = max([c[1] for c in type_map])
    except ValueError: return
    ls = [[0 for _ in range(xmax+1)] for _ in range(ymax+1)]
    for k in type_map:
        ls[k[1]][k[0]] = type_map[k]
    print '\t',
    for x in range(xmax): print str(x)+' '*(2-len(str(x))),
    print '\n'
    for y in range(len(ls)):
        l = str(y)+'\t'
        for x in range(len(ls[y])):
            s=type_letter(ls[y][x])
            if (x,y) == target: s+='T'
            l+=s+' '*(3-len(s))
        print l
    print
def print_dist(border):
    global d
    xmax = max([c[0] for c in d])
    ymax = max([c[1] for c in d])
    ls = [[0 for _ in range(xmax+1)] for _ in range(ymax+1)]
    for k in d:
        ls[k[1]][k[0]] = d[k]
    print '\t',
    for x in range(xmax): print str(x)+' '*(6-len(str(x))),
    print '\n'
    for y in range(len(ls)):
        l = str(y)+'\t'
        for x in range(len(ls[y])):
            s=str(ls[y][x])
            if (x,y) in border:
                if type(border[x,y]) == type([]):
                    for t in border[x,y]: s+='-'+str(t)
                else: s+='-'+str(border[x,y])
            l+=s+' '*(7-len(s))
        print l
    print
target = (14,778) #reverse?
#target = (10,10)
depth = 11541
#depth = 510
X,Y=2000,2000
geo_ind = {(0,0):0, target:0}
for x in range(X): geo_ind[(x,0)] = x*16807
for y in range(Y): geo_ind[(0,y)] = y*48271
type_map = {}
def erosion(x,y):
    global geo_ind
    if geo_ind.has_key((x,y)): ind = geo_ind[(x,y)]
    else:
        ind = erosion(x-1,y)*erosion(x,y-1)
        geo_ind[(x,y)] = ind
    return ((ind+depth)%20183)
for y in range(1500):
    for x in range(1500):
        erosion(x,y)
def adj(c): return [(c[0]-1,c[1]), (c[0]+1,c[1]), (c[0],c[1]-1), (c[0],c[1]+1)]
def get_type(c):
    global type_map
    if not type_map.has_key(c): type_map[c] = erosion(*c)%3
    return type_map[c]
def can_tv(c,e):
    if type(e) == type([]):
        return sum([1 for t in e if t != get_type(c)])
    elif get_type(c) == e: return False
    if c == target and e == 1: return False
    return True
def move_time(c,e):
    if can_tv(c,e): return 1
    return 8
#print sum([erosion(x,y)%3 for x in range(target[0]+1) for y in range(target[1]+1)])
def type_letter(t):
    if t == 2: return '|'
    elif t: return '='
    return '.'
def do():
    border = {(0,0):1}
    d = defaultdict(lambda: 0,{(0,0):0})
    dist_list = []
    while 1:
        #print_dist(border)
        #print_map()
        new_border = {}
        for coord in border:
            for adj_c in adj(coord):
                if adj_c[0] < 0 or adj_c[1] < 0: continue
                if adj_c not in d or d[adj_c] > d[coord]+move_time(adj_c,border[coord]): #note: naive
                    tv_able = can_tv(adj_c,border[coord])
                    if tv_able:
                        if tv_able&1:
                            if type(border[coord]) == int: new_border[adj_c] = border[coord]
                            else:
                                for t in border[coord]:
                                    if can_tv(adj_c,t): new_border[adj_c] = t
                        else: new_border[adj_c] = border[coord]
                        d[adj_c] = d[coord]+1
                    else:
                        d[adj_c] = d[coord]+8
                        new_border[adj_c] = [t for t in range(3) if t != get_type(adj_c)]
                elif d[adj_c] == d[coord]+8 and new_border.has_key(adj_c) and type(new_border[adj_c]) == int:
                    new_border[adj_c] = [t for t in range(3) if t != get_type(adj_c)]
        if target in new_border:
            for c in [c for c in adj(target) if c in border]:
                if border[c] != 1: dist_list.append(d[c]+8)
                else: dist_list.append(d[c]+1)
        if all([c in d for c in adj(target)]):
            mini = min(dist_list)
            if all([mini < d[c] for c in new_border]): break
        else:
            for c in [c for c in adj(target) if c in d]:
                print d[c]
        border = new_border
    print "minimum distance is: %d" % min(dist_list)-10
do()
print max(geo_ind.values())
print min(geo_ind.values())
