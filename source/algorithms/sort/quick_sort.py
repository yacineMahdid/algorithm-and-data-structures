
def quick_sort(items):
    print("Do the quick sort")


def sort(items,low,high):
    if high > low:
        pivot = partition(items, low, high)
        sort(items, low, pivot - 1)
        sort(items, pivot + 1, high)


def partition(items, low, high):
    pivot = 0

    return pivot
