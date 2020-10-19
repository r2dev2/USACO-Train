"""
ID: ronak.b1
LANG: PYTHON3
TASK: sort3
"""
import itertools as it
from queue import Queue


with open("sort3.in", 'r') as fin:
    oglist = [int(i.rstrip()) for i in fin.readlines()][1:]

l = len(oglist)

counts = {1: 0, 2: 0, 3: 0}
for i in oglist:
    counts[i] += 1

uppers = {1: counts[1], 2: counts[1]+counts[2], 3: l}
lowers = {1: 0, 2: counts[1], 3: counts[1]+counts[2]}

def three_summary(lyst):
    count_1 = sum(1 for i in lyst[lowers[1]: uppers[1]] if i == 1)
    count_2 = sum(1 for i in lyst[lowers[2]: uppers[2]] if i == 2)
    count_3 = sum(1 for i in lyst[lowers[3]: uppers[3]] if i == 3)
    return count_1, count_2, count_3

qu = Queue()
qu.put(oglist)
qu2 = Queue()

sorted_list = sorted(oglist)

print(lowers, uppers)
print(sorted_list)

visited = set()
num_switches = 0

def swap_n(n1, n2):
    global num_switches
    lyst = oglist
    q1 = lyst[lowers[n1]: uppers[n1]]
    q2 = lyst[lowers[n2]: uppers[n2]]
    switcheable_in_1 = [i for i, n in enumerate(q1) if n == n2]
    switcheable_in_2 = [i for i, n in enumerate(q2) if n == n1]
    for s1, s2 in zip(switcheable_in_1, switcheable_in_2):
        lyst[lowers[n1]+s1], lyst[lowers[n2]+s2] = q2[s2], q1[s1]
        num_switches += 1


swap_n(1, 2)
swap_n(1, 3)
swap_n(2, 3)


# rang = range

n = 0

for i in it.count(num_switches):
    print(i, qu.qsize())
    while not qu.empty():
        lyst = qu.get()
        if lyst == sorted_list:
            with open("sort3.out", 'w+') as fout:
                print(i, file=fout)
            print(n)
            exit()
        for j in range(l):
            lj = lyst[j]
            if lowers[lj] <= j < uppers[lj]:
                continue
            for k in range(l):
                n += 1
                lk = lyst[k]
                if lyst[j] > lyst[k] and not (lowers[lk] <= k < uppers[lk]):
                    lcopy = lyst[:]
                    lcopy[j], lcopy[k] = lcopy[k], lcopy[j]
                    trs = three_summary(lcopy)
                    if trs not in visited:
                        qu2.put(lcopy)
                        visited.add(trs)
                    tlcopy = tuple(lcopy)
                    # if tlcopy not in visited:
                    #     qu2.put(lcopy)
                    #     visited.add(tlcopy)
    qu = qu2
    qu2 = Queue()
    if qu.empty():
        break

print("dammit")

