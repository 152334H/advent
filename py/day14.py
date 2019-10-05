def do(part, test, show):      #part 1 & 2 are similar, and using a function increases program speed
    scoreboard = [3, 7]             #start scoreboard with given numbers
    elf1, elf2 = [0, 1]             #list of 0,1
    while test(''.join(str(d) for d in scoreboard[-7:]) if part else len(scoreboard)):    #if part 2, give the last 7 recipes, else give the number of recipes
        add = scoreboard[elf1] + scoreboard[elf2]       #sum of the elves score
        if add > 9: scoreboard.append(add/10)           #if the sum has a tens part, add it
        scoreboard.append(add%10)                       #add the ones
        elf1, elf2 = [(scoreboard[elf]+elf+1)%len(scoreboard) for elf in (elf1,elf2)]     #move elf1&2 to where they should be
    print show(scoreboard)

with open('input') as f: input = f.read()[:-1]
given = int(input)

do(0,   #do part 1
    lambda s_len: s_len < given+10,   #while the number of recipes are lower than the given input +10
    lambda sb: ''.join(str(d) for d in sb[-11:-1]) if len(sb)-1 == given+10 else ''.join(str(d) for d in sb[-10:])) #print the last 10 recipes, with off-by-one checking
do(1,   #do part 2
    lambda s: input not in s,         #while no matching recipe has been found
    lambda sb: len(sb)-6 if input == ''.join(str(d) for d in sb[-6:]) else len(sb)-7)  #print the number of recipes -6, with off-by-one checking
