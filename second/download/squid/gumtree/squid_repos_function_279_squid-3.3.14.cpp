static void
msort(struct hstruct *array, size_t nitems, int (*cmp) (struct hstruct *, struct hstruct *))
{
    sort(array, nitems, cmp, 0, nitems - 1);
}