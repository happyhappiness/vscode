h2_stream *h2_mplx_stream_get(h2_mplx *m, int id)
{
    h2_stream *s = NULL;
    int acquired;
    
    if ((enter_mutex(m, &acquired)) == APR_SUCCESS) {
        s = h2_ihash_get(m->streams, id);
        leave_mutex(m, acquired);
    }
    return s;
}