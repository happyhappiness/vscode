apr_status_t h2_mplx_keep_active(h2_mplx *m, h2_stream *stream)
{
    check_data_for(m, stream, 1);
    return APR_SUCCESS;
}