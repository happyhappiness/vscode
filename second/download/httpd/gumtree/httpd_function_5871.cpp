apr_status_t h2_stream_write_eoh(h2_stream *stream, int eos)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(stream);
    
    /* Seeing the end-of-headers, we have everything we need to 
     * start processing it.
     */
    status = h2_mplx_create_task(stream->m, stream);
    if (status == APR_SUCCESS) {
        status = h2_request_end_headers(stream->request, 
                                        stream->m, stream->task, eos);
        if (status == APR_SUCCESS) {
            status = h2_mplx_do_task(stream->m, stream->task);
        }
        if (eos) {
            status = h2_stream_write_eos(stream);
        }
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, stream->m->c,
                      "h2_mplx(%ld-%d): start stream, task %s %s (%s)",
                      stream->m->id, stream->id,
                      stream->request->method, stream->request->path,
                      stream->request->authority);
        
    }
    return status;
}