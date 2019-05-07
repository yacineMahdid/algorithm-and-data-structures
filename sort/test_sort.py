import unittest
from .merge_sort import merge_sort
from .quick_sort import quick_sort


class TestSorting(unittest.TestCase):

    def test_sort(self):
        items = [0, 4, 6, 2, -1, -9, 10, 103, -103]
        self.assertEquals(quick_sort(items), items.sort())


if __name__ == '__main__':
    unittest.main()
