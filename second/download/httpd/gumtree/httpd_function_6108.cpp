apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
                                    apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    if (!output_open(stream)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
                      "h2_stream(%ld-%d): output closed", 
                      stream->session->id, stream->id);
        return APR_ECONNRESET;
    }
    
    stream->response = response;
    if (bb && !APR_BRIGADE_EMPTY(bb)) {
        int move_all = INT_MAX;
        /* we can move file handles from h2_mplx into this h2_stream as many
         * as we want, since the lifetimes are the same and we are not freeing
         * the ones in h2_mplx->io before this stream is done. */
        H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream set_response_pre");
        status = h2_util_move(stream->bbout, bb, 16 * 1024, &move_all,  
                              "h2_stream_set_response");
        H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream set_response_post");
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, stream->session->c,
                  "h2_stream(%ld-%d): set_response(%d)", 
                  stream->session->id, stream->id, response->http_status);
    return status;
}