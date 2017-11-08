apr_size_t h2_stream_set_size(h2_stream_set *sp)
{
    return sp->list->nelts;
}