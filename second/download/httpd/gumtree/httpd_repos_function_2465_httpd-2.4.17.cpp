int h2_stream_set_is_empty(h2_stream_set *sp)
{
    AP_DEBUG_ASSERT(sp);
    return sp->list->nelts == 0;
}