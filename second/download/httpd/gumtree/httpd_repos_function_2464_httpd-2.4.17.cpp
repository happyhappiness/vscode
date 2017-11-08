void h2_stream_set_remove_all(h2_stream_set *sp)
{
    sp->list->nelts = 0;
}