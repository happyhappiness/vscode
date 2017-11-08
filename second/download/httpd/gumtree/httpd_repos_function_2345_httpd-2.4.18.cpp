h2_io *h2_io_set_remove(h2_io_set *sp, h2_io *io)
{
    int i;
    for (i = 0; i < sp->list->nelts; ++i) {
        h2_io *e = h2_io_IDX(sp->list, i);
        if (e == io) {
            remove_idx(sp, i);
            return e;
        }
    }
    return NULL;
}