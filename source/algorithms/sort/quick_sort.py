# Yacine Mahdid 2018-11-15 (Foundation of Algorithm)


# Wrapper function to allow for ease of use
def quick_sort(items):
    sort(items, 0, len(items)-1)


# Recursive sorting algorithm that will partition the items from a pivot first
def sort(items, low, high):
    if high > low:
        pivot_index = partition(items, low, high)
        sort(items, low, pivot_index - 1)
        sort(items, pivot_index + 1, high)


# Partition is where the sorting take place, we put everything that is smaller than
# the pivot to the left and everything bigger to the right.
# We do that recursively, when we are done the list is sorted
def partition(items, low, high):
    pivot = items[low]
    index = low
    for i in range(low+1, high+1):
        if items[i] < pivot:
            index = index + 1
            temp = items[i]
            items[i] = items[index]
            items[index] = temp

    pivot_index = index
    temp = items[low]
    items[low] = items[pivot_index]
    items[pivot_index] = temp
    return pivot_index


items_test = [1, 105, 3, 2, 43, 89, -1, 5, 6, 0]

quick_sort(items_test)

print(items_test)
