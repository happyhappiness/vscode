static void purge_streams(h2_mplx *m)
{
    if (!h2_ihash_empty(m->spurge)) {
        while(!h2_ihash_iter(m->spurge, purge_stream, m)) {
            /* repeat until empty */
        }
        h2_ihash_clear(m->spurge);
    }
}