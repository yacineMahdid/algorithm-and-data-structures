def iterative_search(items, key):
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


def recursive_search(items, key):
    print("Searching recusively the items")


items_to = [1, 2, 3, 4, 5, 6, 7, 8, 13, 104, 105]
key_to = 105

index = iterative_search(items_to, key_to)
print(index)
print(items_to[index])
