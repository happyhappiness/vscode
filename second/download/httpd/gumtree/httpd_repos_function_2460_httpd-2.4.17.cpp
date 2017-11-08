h2_stream *h2_stream_set_get(h2_stream_set *sp, int stream_id)
{
    /* we keep the array sorted by id, so lookup can be done
     * by bsearch.
     */
    h2_stream key;
    h2_stream *pkey, **ps;
    memset(&key, 0, sizeof(key));
    key.id = stream_id;
    pkey = &key;
    ps = bsearch(&pkey, sp->list->elts, sp->list->nelts, 
                             sp->list->elt_size, h2_stream_id_cmp);
    return ps? *ps : NULL;
}