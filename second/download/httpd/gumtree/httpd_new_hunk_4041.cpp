 * once we have all the response headers. The response body will be
 * read by the session using the callback we supply.
 */
static apr_status_t submit_response(h2_session *session, h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    h2_response *response = h2_stream_get_response(stream);
    int rv = 0;
    AP_DEBUG_ASSERT(session);
    AP_DEBUG_ASSERT(stream);
    AP_DEBUG_ASSERT(response || stream->rst_error);
    
    if (stream->submitted) {
        rv = NGHTTP2_PROTOCOL_ERROR;
    }
    else if (response && response->headers) {
        nghttp2_data_provider provider, *pprovider = NULL;
        h2_ngheader *ngh;
        const h2_priority *prio;
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03073)
                      "h2_stream(%ld-%d): submit response %d",
                      session->id, stream->id, response->http_status);
        
        if (response->content_length != 0) {
            memset(&provider, 0, sizeof(provider));
            provider.source.fd = stream->id;
            provider.read_callback = stream_data_cb;
            pprovider = &provider;
        }
        
        /* If this stream is not a pushed one itself,
         * and HTTP/2 server push is enabled here,
         * and the response is in the range 200-299 *),
         * and the remote side has pushing enabled,
         * -> find and perform any pushes on this stream
         *    *before* we submit the stream response itself.
