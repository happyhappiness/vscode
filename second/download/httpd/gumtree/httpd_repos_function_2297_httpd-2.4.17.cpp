void h2_io_set_destroy_all(h2_io_set *sp)
{
    int i;
    for (i = 0; i < sp->list->nelts; ++i) {
        h2_io *io = h2_io_IDX(sp->list, i);
        h2_io_destroy(io);
    }
    sp->list->nelts = 0;
}