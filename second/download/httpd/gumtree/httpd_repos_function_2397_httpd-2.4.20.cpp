apr_status_t h2_io_set_add(h2_io_set *sp, h2_io *io)
{
    h2_io *existing = h2_io_set_get(sp, io->id);
    if (!existing) {
        int last;
        APR_ARRAY_PUSH(sp->list, h2_io*) = io;
        /* Normally, streams get added in ascending order if id. We
         * keep the array sorted, so we just need to check if the newly
         * appended stream has a lower id than the last one. if not,
         * sorting is not necessary.
         */
        last = sp->list->nelts - 1;
        if (last > 0 
            && (h2_io_IDX(sp->list, last)->id 
                < h2_io_IDX(sp->list, last-1)->id)) {
                h2_io_set_sort(sp);
            }
    }
    return APR_SUCCESS;
}