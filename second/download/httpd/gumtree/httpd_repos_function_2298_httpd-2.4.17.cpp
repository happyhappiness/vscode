void h2_io_set_remove_all(h2_io_set *sp)
{
    sp->list->nelts = 0;
}