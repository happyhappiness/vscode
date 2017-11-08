static void remove_idx(h2_io_set *sp, int idx)
{
    int n;
    --sp->list->nelts;
    n = sp->list->nelts - idx;
    if (n > 0) {
        /* Close the hole in the array by moving the upper
         * parts down one step.
         */
        h2_io **selts = (h2_io**)sp->list->elts;
        memmove(selts + idx, selts + idx + 1, n * sizeof(h2_io*));
    }
}