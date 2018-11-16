
def quick_sort(items):
    print("Do the quick sort")

def sort(items,low,high):
    pivot = 0;
    if high > low:
        partition(items, low, high, pivot)
        sort(items, low, pivot - 1)
        sort(items, pivot + 1, high)

def partition(items, low, high, pivot):