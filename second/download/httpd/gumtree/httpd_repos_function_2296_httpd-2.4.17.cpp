h2_io *h2_io_set_remove(h2_io_set *sp, h2_io *io)
{
    int i;
    for (i = 0; i < sp->list->nelts; ++i) {
        h2_io *e = h2_io_IDX(sp->list, i);
        if (e == io) {
            int n;
            --sp->list->nelts;
            n = sp->list->nelts - i;
            if (n > 0) {
                /* Close the hole in the array by moving the upper
                 * parts down one step.
                 */
                h2_io **selts = (h2_io**)sp->list->elts;
                memmove(selts+i, selts+i+1, n * sizeof(h2_io*));
            }
            return e;
        }
    }
    return NULL;
}