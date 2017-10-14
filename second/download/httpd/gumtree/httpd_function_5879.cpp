static apr_status_t h2_stream_input_flush(h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    if (stream->bbin && !APR_BRIGADE_EMPTY(stream->bbin)) {

        status = h2_mplx_in_write(stream->session->mplx, stream->id, stream->bbin);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, stream->session->mplx->c,
                          "h2_stream(%ld-%d): flushing input data",
                          stream->session->id, stream->id);
        }
    }
    return status;
}