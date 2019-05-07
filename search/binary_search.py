def iterative_binary_search(items, key):
    # Inputs
    # items = list of sorted items
    # key = item we are looking for

    # Error checking
    if len(items) == 0:
        return None

    # Find the key in the items
    min_index = 0
    max_index = len(items) - 1
    middle_index = int((max_index+min_index)/2)
    while min_index <= max_index:
        print("Min index = " + str(min_index) + " ; Max index = " + str(max_index) + "; Middle = " + str(middle_index))
        if items[middle_index] == key:
            return middle_index  # if found it return the index
        elif items[middle_index] > key:
            max_index = middle_index-1
        elif items[middle_index] < key:
            min_index = middle_index+1
        # Update the middle index and the other index
        middle_index = int((max_index+ min_index)/2)

    return None


# Wrapper functions for ease of use
def recursive_binary_search(items, key):
    min_index = 0
    max_index = len(items)-1
    return search(items, key, min_index, max_index)


def search(items, key, min_index, max_index):
    # Inputs
    # items = list of sorted items
    # key = item we are looking for
    # min_index = lower bound
    # max_index = upper bound

    # Error checking
    if len(items) == 0 or min_index > max_index:
        return None

    middle_index = int((min_index+max_index)/2)

    # Base case of recursion
    if items[middle_index] == key:
        return middle_index
    # Updating the min and max
    elif items[middle_index] > key:
        max_index = middle_index - 1
    elif items[middle_index] < key:
        min_index = middle_index + 1

    # Recursive call
    return search(items, key, min_index, max_index)


items_to = [1, 2, 3, 4, 5, 6, 7, 8, 13, 104, 105]
key_to = 7.6

index = recursive_binary_search(items_to, key_to)
print(index)
print(items_to[index])
