n = 0
with open('newinput') as f: s = [l.strip() for l in f.readlines()] #list of lines with the trailing whitespace at the end and start removed
s = s[1:]
system = [] #units, hp, weak/immunities?, dmg, atktype, initiative
infect = []
while s[0] != '': system.append(s.pop(0).split(':'))
s = s[2:]
while s: infect.append(s.pop(0).split(':'))
for army in [system, infect]:
    for i in range(len(army)):
        d = {'weak': '', 'immune': ''}
        weak, immu = '',''
        if len(army[i]) > 5:
            cond = army[i][2].split('; ')
            if len(cond) == 2:
                refer = cond[1].split('-')
                d[refer[0]] = ''.join(refer[1:])
            refer = cond[0].split('-')
            d[refer[0]] = ''.join(refer[1:])
            del army[i][2]
        army[i].insert(2,d)
        for n in [0,1,3,5]:
            army[i][n] = int(army[i][n])
def get_eff_pwr(army): #efftive_power:group
    d = {}
    for group in army:
        eff = group[0]*group[3]
        if eff not in d: d[eff] = [group]
        else: d[eff].append(group)
    return d
def get_init(groups): #initiative:group
    d = {}
    for g in groups:
        i = g[5]
        d[i] = g #note: there are no dups
    return d
def damage(a,d):
    dt = a[4]
    if dt in d[2]['weak']: return 2
    if dt in d[2]['immune']: return 0
    return 1
def boost(n):
    global system
    for g in system: g[3]+=n
def do_battle(inf,sys, t=None):
    while 1:
        if t and time()-t > 20:
            print "breaking"
            return 'break'
        for army in [inf, sys]:
            a_eff = get_eff_pwr(army)
            enemy = [inf, sys][id(army) == id(inf)][:]
            ls = reversed(sorted(a_eff.keys()))
            for eff in ls: #in decresing order of effective power
                init_d = get_init(a_eff[eff])
                for init in reversed(sorted(init_d.keys())):
                    if not init_d[init][0]:
                        init_d[init].append(None)
                        continue
                    to_attack = []
                    max_dmg = 0
                    for egroup in enemy:
                        dmg = eff*damage(init_d[init], egroup)
                        if dmg > max_dmg:
                            to_attack = [egroup]
                            max_dmg = dmg
                        elif dmg == max_dmg:
                            to_attack.append(egroup)
                    if not max_dmg: to_attack = [None]
                    if len(to_attack) > 1:
                        dg_pwr = get_eff_pwr(to_attack)
                        to_attack=dg_pwr[max(dg_pwr.keys())]
                        if len(to_attack) > 1:
                            dg_init = get_init(to_attack)
                            to_attack = [dg_init[max(dg_init.keys())]]
                    if len(to_attack):
                        if to_attack[0]: enemy.remove(to_attack[0])
                        init_d[init].append(to_attack[0])
                    else: init_d[init].append(None)
        g_init = get_init(inf+sys)
        for init in reversed(sorted(g_init.keys())):
            if init not in g_init:
                continue
            target = g_init[init].pop()
            if target==None: continue
            enemy = [inf, sys][bool(target in sys)]
            target = enemy.index(target)
            killed = g_init[init][0]*g_init[init][3]*damage(g_init[init],enemy[target])/enemy[target][1]
            if enemy[target][0]:
                enemy[target][0]-=min(killed,enemy[target][0])
            if not enemy[target][0]:
                del enemy[target]
        if all([sum([v[0] for v in a]) for a in [inf,sys]]): continue
        break
    total = [sum([v[0] for v in a]) for a in [inf,sys]]
    print "%d: %s: %d" % (n,["system","infection"][bool(total[0])], sum(total))
    return ["system","infection"][bool(total[0])]
rtr,n = '',0
while n < 50:
    inf_cpy = []
    for l in infect: inf_cpy.append(l[:])
    sys_cpy = []
    for l in system: sys_cpy.append(l[:])
    rtr = do_battle(inf_cpy,sys_cpy)
    boost(1)
    n+=1

