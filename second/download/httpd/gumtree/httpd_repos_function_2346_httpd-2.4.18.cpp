h2_io *h2_io_set_pop_highest_prio(h2_io_set *set)
{
    /* For now, this just removes the first element in the set.
     * the name is misleading...
     */
    if (set->list->nelts > 0) {
        h2_io *io = h2_io_IDX(set->list, 0);
        remove_idx(set, 0);
        return io;
    }
    return NULL;
}