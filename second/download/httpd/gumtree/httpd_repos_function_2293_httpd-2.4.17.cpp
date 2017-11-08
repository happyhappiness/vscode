h2_io *h2_io_set_get_highest_prio(h2_io_set *set)
{
    h2_io *highest = NULL;
    int i;
    for (i = 0; i < set->list->nelts; ++i) {
        h2_io *io = h2_io_IDX(set->list, i);
        if (!highest /*|| io-prio even higher */ ) {
            highest = io;
        }
    }
    return highest;
}