static void
msort(struct hstruct *array, size_t nitems, int (*cmp) (struct hstruct *, struct hstruct *))
{
    sort(array, (int)nitems, cmp, 0, (int)(nitems - 1));
}