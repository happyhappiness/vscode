h2_stream *h2_stream_set_remove(h2_stream_set *sp, h2_stream *stream)
{
    int i;
    for (i = 0; i < sp->list->nelts; ++i) {
        h2_stream *s = H2_STREAM_IDX(sp->list, i);
        if (s == stream) {
            int n;
            --sp->list->nelts;
            n = sp->list->nelts - i;
            if (n > 0) {
                /* Close the hole in the array by moving the upper
                 * parts down one step.
                 */
                h2_stream **selts = (h2_stream**)sp->list->elts;
                memmove(selts+i, selts+i+1, n * sizeof(h2_stream*));
            }
            return s;
        }
    }
    return NULL;
}