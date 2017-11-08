apr_status_t h2_mplx_keep_active(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_stream *s = h2_ihash_get(m->streams, stream_id);
        if (s) {
            h2_iq_append(m->readyq, stream_id);
        }
        leave_mutex(m, acquired);
    }
    return status;
}