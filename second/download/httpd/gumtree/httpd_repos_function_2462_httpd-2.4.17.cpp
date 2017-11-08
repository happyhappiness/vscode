apr_status_t h2_stream_set_add(h2_stream_set *sp, h2_stream *stream)
{
    h2_stream *existing = h2_stream_set_get(sp, stream->id);
    if (!existing) {
        int last;
        APR_ARRAY_PUSH(sp->list, h2_stream*) = stream;
        /* Normally, streams get added in ascending order if id. We
         * keep the array sorted, so we just need to check of the newly
         * appended stream has a lower id than the last one. if not,
         * sorting is not necessary.
         */
        last = sp->list->nelts - 1;
        if (last > 0 
            && (H2_STREAM_IDX(sp->list, last)->id 
                < H2_STREAM_IDX(sp->list, last-1)->id)) {
            h2_stream_set_sort(sp);
        }
    }
    return APR_SUCCESS;
}