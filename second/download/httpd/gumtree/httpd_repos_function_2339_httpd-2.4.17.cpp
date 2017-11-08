apr_status_t h2_to_h1_flush(h2_to_h1 *to_h1)
{
    apr_status_t status = APR_SUCCESS;
    if (!APR_BRIGADE_EMPTY(to_h1->bb)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, to_h1->m->c,
                      "h2_to_h1(%ld-%d): flush request bytes", 
                      to_h1->m->id, to_h1->stream_id);
        
        status = h2_mplx_in_write(to_h1->m, to_h1->stream_id, to_h1->bb);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, to_h1->m->c,
                          APLOGNO(02946) "h2_request(%d): pushing request data",
                          to_h1->stream_id);
        }
    }
    return status;
}