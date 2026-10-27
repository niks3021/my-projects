import random
target = "i like to code sometimes but maybe i just like the feeling of doing something cool idk u tell me pls i guess"
def generatestring(length):
    generatedstring = ""
    for _ in range(length):
        rand = random.randint(32,126)
        generatedstring+=chr(rand)
    return generatedstring
def fitness(check,target):
    score = 0
    for c,t in zip(check,target):
        if(c==t):
            score+=1
    return score
def goodparents(currentgen):
    good = currentgen[:10]
    parent1,parent2,parent3 = random.sample(good,3)
    return parent1,parent2,parent3
def nextgen(parent1,parent2,parent3,target):
    slicepoint = random.randint(1,int(len(target)/2))
    slicepoint2 = random.randint(int(len(target)/2),len(target)-1)
    slice1 = parent1[:slicepoint]
    slice2 = parent2[slicepoint:slicepoint2]
    slice3 = parent3[slicepoint2:]
    return slice1+slice2+slice3
def mutate(child, num_mutations=1):
    child_list = list(child)
    for _ in range(num_mutations):
        index_to_mutate = random.randint(0, len(child_list) - 1)
        child_list[index_to_mutate] = chr(random.randint(32, 126))
    return "".join(child_list)
gencount =1
bestoverall = 0
currentgen = []
maxgeneration = 500
currentgen = [generatestring(len(target)) for _ in range(maxgeneration)]
while bestoverall < len(target):
    sortgenerationbyfitness = sorted(currentgen,key = lambda c:fitness(c,target),reverse= True)
    best = sortgenerationbyfitness[0]
    new_gen = [best] 
    bestoverall = fitness(target,sortgenerationbyfitness[0])
    while len(new_gen) < maxgeneration:
        p1, p2, p3 = goodparents(sortgenerationbyfitness)
        child = nextgen(p1, p2, p3, target)
        child = mutate(child)
        new_gen.append(child)
    gencount+=1
    currentgen = new_gen
    print(f"current generation {gencount} closest candidate {currentgen[0]} current score {bestoverall}/{len(target)}")

print(f"Target found at {gencount} generations")
