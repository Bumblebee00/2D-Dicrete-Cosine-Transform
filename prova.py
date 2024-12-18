w = 5
n = 0
all_arg = set()

for u in range(0,w):
    f_uesimo = [(x/2 + 0.25)*u/w for x in range(0,w)]
    n += len(f_uesimo)
    f_uesimo_mod = [el for el in f_uesimo if el<1]
    all_arg.update(f_uesimo_mod)
    # print(f_uesimo)
    # print(f_uesimo_mod)
    # print("-----------------------")

print("w: ", w, ", needed: ", len(all_arg), ", done: ", n, ", ratio: ", n/len(all_arg), "4*w: ", 4*w)

# print(sorted(list(all_arg))[0:10])

prova = [n/(4*w) for n in range(0,4*w)]

for i in range(0,4*w):
    if prova[i] not in all_arg:
        print("Not found: ", prova[i])