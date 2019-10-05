with open('input') as f: coords = [tuple(map(int,l.strip().split(','))) for l in f.readlines()] #list of coordinates
constell = []   #constellations as sets
def dist(c1,c2): return sum(map(lambda a:abs(a[0]-a[1]),zip(c1,c2)))    #distance between two coordinates
def merge(cons):
    for c in cons:  #for coordinate in constellation
        for s in (s for s in constell if s != cons):    #going over other constellations
            for dc in (dc for dc in s if dist(c,dc) <= 3):  #if the constellations could be merged
                s.update(cons)                      #add to one
                del constell[constell.index(cons)]  #deleting the other
                return 0
    return 1
for c in coords:
    for adj_c in (a for a in coords if a != c and dist(c,a) <= 3): #for all adjacent coordinates given
        for s in constell:  #search through existing constellations
            if adj_c in s:  #if an adjacent coordinate is already inside
                s.add(c)#add the current coordinate to the constellation
                break   #and deny the else
        else: constell.append(set([c,adj_c]))   #create a new constellation if adjacent one isn't in one
        break
    else: constell.append(set([c])) #if the current coordinate didn't have a single adjacent one
i = 0
while i != len(constell): i += merge(constell[i])   #only increments index after the current constellation is finally merged
print i#== len(constell)
