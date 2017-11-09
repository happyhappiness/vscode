static void purge_streams(h2_mplx *m, int lock)
{
    if (!h2_ihash_empty(m->spurge)) {
        H2_MPLX_ENTER_MAYBE(m, lock);
        while (!h2_ihash_iter(m->spurge, stream_destroy_iter, m)) {
            /* repeat until empty */
        }
        H2_MPLX_LEAVE_MAYBE(m, lock);
    }
}