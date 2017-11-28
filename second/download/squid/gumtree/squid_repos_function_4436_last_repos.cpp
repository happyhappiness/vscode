static void
sort(struct hstruct *array, int nitems, int (*cmp) (struct hstruct *, struct hstruct *), int begin, int end)
{
    if (end > begin) {
        int l = begin + 1;
        int r = end;
        while (l < r) {
            int pivot = begin;
            if (cmp(&array[l], &array[pivot]) <= 0) {
                l += 1;
            } else {
                r -= 1;
                swap(&array[l], &array[r]);
            }
        }
        l -= 1;
        swap(&array[begin], &array[l]);
        sort(array, nitems, cmp, begin, l);
        sort(array, nitems, cmp, r, end);
    }
}