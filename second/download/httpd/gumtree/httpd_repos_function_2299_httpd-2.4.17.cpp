int h2_io_set_is_empty(h2_io_set *sp)
{
    AP_DEBUG_ASSERT(sp);
    return sp->list->nelts == 0;
}