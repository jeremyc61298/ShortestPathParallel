# GenerateTests.py
# Jeremy Campbell
# Script to Generate Test Cases for ShortestPathParallel

import random

numLocations = 1000
print(numLocations)
numRoads = 4000
print(numRoads)

existingRoads = [];

# Print out roads in the format - firstLocation secondLocation distance
# Roads are non-repeating and cannot go from one location to the same location
for i in range(numRoads):
    first = random.randint(0, numLocations - 1)
    second = random.randint(0, numLocations - 1)
    distance = random.randint(1, 11)

    while (first == second or (str(first) + " " + str(second)) in existingRoads):
        first = random.randint(0, numLocations - 1)
        
    existingRoads.append(str(first) + " " + str(second))
    print(first, " ", second, " ", distance)

# Print out some routes to test with
numRoutes = 50
print(numRoutes)

# I want at least one route to be max locations long
print(numLocations, " ", end="")
for i in range(numLocations):
    print(random.randint(0, numLocations - 1), " ", end="")

print()

for i in range(numRoutes - 1):
    locationsInRoute = random.randint(2, 31)
    print(locationsInRoute, " ", end="")

    for j in range(locationsInRoute):
        print(random.randint(0, numLocations - 1), " ", end="")

    print()
    