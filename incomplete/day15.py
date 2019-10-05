from collections import defaultdict
def print_map():     #test function
    head = '\t'
    for i in range(len(copy[0])): head += str(i%10)
    print head
    i = 0
    for l in copy:
        print str(i)+'\t'+''.join(l)
        i += 1
def get_floor(coord): return copy[coord[0]][coord[1]]
def distance_map(start):
    d = defaultdict(lambda: -1)
    border = [start]
    while border:
        new_border = []
        for coord in border:
            for adj_c in adj(coord):
                if adj_c not in d.keys() and get_floor(adj_c) == '.':
                    new_border.append(adj_c) #does unnecessary appends, but faster anyway
                    d[adj_c] = d[coord] +1
        border = new_border
    return d
def adj(c): return [(c[0]-1,c[1]), (c[0]+1,c[1]), (c[0],c[1]-1), (c[0],c[1]+1)]
def attack(c, enemy, enemy_ls):
    kill = minimum((p for p in adj(c) if get_floor(p) == enemy), lambda v: v == None, lambda p: enemy_ls[p])
    if enemy == 'E': enemy_ls[kill] -= 3
    else: enemy_ls[kill] -= ELF_PWR
    if enemy_ls[kill] < 1: #if enemy should die
        del enemy_ls[kill]
        copy[kill[0]][kill[1]] = '.'
def minimum(gen, null, v):
    mini = 99999
    low_list = []
    for thing in gen:
        value = v(thing)
        if not null(value):
            if value <= mini:
                if value < mini: low_list = [thing]
                else: low_list.append(thing)
                mini = value
    if low_list: return min(low_list)
    return None
def do_turn(race, coord):
    if race == 'E':
        race_d = elves
        enemy_d = gobs
        enemy = 'G'
    else:
        race_d = gobs
        enemy_d = elves
        enemy = 'E'
    if not enemy_d.keys(): return -1
    if coord not in race_d.keys(): return 0
    if enemy in [get_floor(c) for c in adj(coord)]: # if something to attack
        attack(coord, enemy, enemy_d)
    else:
        dist_dict = distance_map(coord)
        chosen = minimum( (c for p in enemy_d for c in adj(p)), lambda x: x == -1, lambda c: dist_dict[c])
        if not chosen: return 0
        if chosen not in adj(coord):
            chosen_dist = distance_map(chosen)
            chosen = minimum(adj(coord), lambda v: v == -1, lambda c: chosen_dist[c])
        copy[y][x] = '.'
        copy[chosen[0]][chosen[1]] = race
        race_d[chosen] = race_d[coord]
        del race_d[coord]

        if enemy in [get_floor(c) for c in adj(chosen)]: # if something to attack
            attack(chosen, enemy, enemy_d)
    return 0

ELF_PWR = 3
ADD = 20        #cleanup soon
tested = []
lowest = 999
while ADD != -1:
    if ELF_PWR in tested or ELF_PWR > lowest:
        if ELF_PWR > lowest:
            ADD /= -2
            ELF_PWR += ADD
        ELF_PWR += ADD
        continue
    with open('input') as f: copy = [list(l.strip()) for l in f.readlines()] #list of lines with the trailing whitespace at the end and start removed
    gobs = defaultdict(lambda: None)
    elves = defaultdict(lambda: None)
    for y in range(len(copy)):
	for x in range(len(copy[y])):
	    if copy[y][x] == 'E': elves[(y,x)] = 200
	    if copy[y][x] == 'G': gobs[(y,x)] = 200
    turn = 0
    ELF_C = len(elves.keys())
    while gobs.keys() and elves.keys():
	turn += 1
        oe = elves.copy()
	for y,x in sorted(gobs.keys() + elves.keys()):
            if do_turn((lambda c: 'E' if c in oe else 'G')((y,x)), (y,x)):
		turn -= 1
		break
    if gobs.keys(): race_d = gobs
    else: race_d = elves
    if ELF_PWR == 3: print "part 1: %d" % (turn*sum(race_d.values()))
    else: 
        if (race_d == gobs or len(elves.keys()) < ELF_C):
            print "ELF POWER %d is insufficient" % ELF_PWR
            if ADD < 0: ADD /= -2
        else:
            print "elf power %d is potentially sufficient: %d" % (ELF_PWR, turn *sum(race_d.values()))
            if ELF_PWR < lowest: lowest = ELF_PWR
            if ADD > -1: ADD /= -2
    tested.append(ELF_PWR)
    ELF_PWR += ADD
print "lowest sufficient tested power: %d" % lowest
