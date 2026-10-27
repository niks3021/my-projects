import random

def fitness(target, attempt):
    score = 0
    for a, t in zip(attempt, target):
        if a == t:
            score += 1
    return score

def generator(length):
    possibleattempt = ""
    for _ in range(length):
        randomchar = random.randint(32, 126)
        possibleattempt += chr(randomchar)
    return possibleattempt

def goodparents(sorted_gen):
    top_candidates = sorted_gen[:10]  
    parent1, parent2 = random.sample(top_candidates, 2)
    return parent1, parent2

def nextgen(parent1, parent2, target):
    randompoint = random.randint(1, len(target) - 1)
    slice1 = parent1[:randompoint]
    slice2 = parent2[randompoint:]
    return slice1 + slice2

def mutate(child, num_mutations=1):
    child_list = list(child)
    for _ in range(num_mutations):
        index_to_mutate = random.randint(0, len(child_list) - 1)
        child_list[index_to_mutate] = chr(random.randint(32, 126))
    return "".join(child_list)
def evolve_island(island, target, population_size, stagnant_gens):
    sorted_island = sorted(island, key=lambda c: fitness(target, c), reverse=True)
    best_candidate = sorted_island[0]
    best_score = fitness(target, best_candidate)
    
    num_mutations = 1
    if stagnant_gens > 15:
        num_mutations = min(3, 1 + (stagnant_gens // 20))
    new_island = [best_candidate] 
    while len(new_island) < population_size:
        p1, p2 = goodparents(sorted_island)
        child = nextgen(p1, p2, target)
        child = mutate(child, num_mutations=num_mutations)
        new_island.append(child)
        
    return new_island, sorted_island, best_candidate, best_score
target = "Hello my name is sir geraldine bartholomew the 3rd"                                                                                                               
target_length = len(target)
island_size = 1000
migration_interval = 5 

island_A = [generator(target_length) for _ in range(island_size)]
island_B = [generator(target_length) for _ in range(island_size)]
generation_count = 1
last_best_score_A = 0
last_best_score_B = 0
stagnant_A = 0
stagnant_B = 0
best_overall_score = 0
while best_overall_score < target_length:
    island_A, sorted_A, best_A, score_A = evolve_island(
        island_A, target, island_size, stagnant_A
    )
    if score_A > last_best_score_A:
        stagnant_A = 0
        last_best_score_A = score_A
    else:
        stagnant_A += 1
    island_B, sorted_B, best_B, score_B = evolve_island(
        island_B, target, island_size, stagnant_B
    )
    if score_B > last_best_score_B:
        stagnant_B = 0
        last_best_score_B = score_B
    else:
        stagnant_B += 1
    if score_A >= score_B:
        overall_best = best_A
        best_overall_score = score_A
        winning_island = "A"
    else:
        overall_best = best_B
        best_overall_score = score_B
        winning_island = "B"

    migrated_flag = ""
    if generation_count % migration_interval == 0:
        island_B[-1] = best_A
        island_A[-1] = best_B
        migrated_flag = " | ⇄ MIGRATED"
    print(
        f"Gen {generation_count:4d} | "
        f"Best ({winning_island}): '{overall_best}' | "
        f"Score: {best_overall_score:2d}/{target_length}"
        f"{migrated_flag}"
    )
    if best_overall_score == target_length:
        print(f"\nTarget guessed successfully on Island {winning_island} in {generation_count} generations!")
        break
    generation_count += 1