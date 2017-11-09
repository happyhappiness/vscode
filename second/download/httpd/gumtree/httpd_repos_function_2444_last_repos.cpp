apr_status_t h2_mplx_out_open(h2_mplx *m, int stream_id, h2_bucket_beam *beam)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else {
        status = out_open(m, stream_id, beam);
    }

    H2_MPLX_LEAVE(m);
    return status;
}