h2_io *h2_io_set_get(h2_io_set *sp, int stream_id)
{
    /* we keep the array sorted by id, so lookup can be done
     * by bsearch.
     */
    h2_io **ps;
    h2_io key;
    h2_io *pkey = &key;

    memset(&key, 0, sizeof(key));
    key.id = stream_id;
    ps = bsearch(&pkey, sp->list->elts, sp->list->nelts, 
                         sp->list->elt_size, h2_stream_id_cmp);
    return ps? *ps : NULL;
}