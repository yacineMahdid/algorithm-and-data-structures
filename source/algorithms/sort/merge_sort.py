# Yacine Mahdid 2018-11-15 (Foundation of Algorithm)


# Wrapper functions to be easy to call
def merge_sort(items):
    sort(items,0,len(items)-1)


# Sorting part of merge sort
# We divide the list into two part and we recurse on the left and right
# Before we merge. Base case here is when left is equal to right index
def sort(items, left, right):
    if left < right:
        middle = int((left+right)/2)
        sort(items, left, middle)
        sort(items, middle+1, right)
        merge(items, left, middle, right)


# Here we merge two part of the array together in the right order. This
# is the part which is doing the sorting
def merge(items, left, middle, right):
    # Create the two arrays to store the left and right content
    left_items = items[left:(middle+1)]
    right_items = items[(middle+1):(right+1)]

    left_index = 0
    right_index = 0
    max_left = (middle-left)
    max_right = (right-(middle+1))

    # Here we go through each index we need to check
    for current_index in range(left, right+1):

        if left_index > max_left and right_index <= max_right:  # Nothing left in the left, put the right
            items[current_index] = right_items[right_index]
            right_index = right_index + 1
        elif right_index > max_right and left_index <= max_left:  # Nothing left in the right, put the left
            items[current_index] = left_items[left_index]
            left_index = left_index + 1
        elif left_items[left_index] <= right_items[right_index]:  # Left is smaller than right item put it in list
            items[current_index] = left_items[left_index]
            left_index = left_index + 1
        elif right_items[right_index] <= left_items[left_index]:  # Right is smaller than left item put it in list
            items[current_index] = right_items[right_index]
            right_index = right_index + 1


items_test = [1, 105, 3, 2, 43, 89, 5, 6, 0]

merge_sort(items_test)

print(items_test)

