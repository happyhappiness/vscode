apr_status_t h2_to_h1_end_headers(h2_to_h1 *to_h1, h2_task *task, int eos)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, to_h1->m->c,
                  "h2_to_h1(%ld-%d): end headers", 
                  to_h1->m->id, to_h1->stream_id);
    
    if (to_h1->eoh) {
        return APR_EINVAL;
    }
    
    if (!to_h1->seen_host) {
        /* Need to add a "Host" header if not already there to
         * make virtual hosts work correctly. */
        if (!to_h1->authority) {
            return APR_BADARG;
        }
        apr_table_set(to_h1->headers, "Host", to_h1->authority);
    }

    if (eos && to_h1->chunked) {
        /* We had chunking figured out, but the EOS is already there.
         * unmark chunking and set a definitive content-length.
         */
        to_h1->chunked = 0;
        apr_table_setn(to_h1->headers, "Content-Length", "0");
    }
    else if (to_h1->chunked) {
        /* We have not seen a content-length. We therefore must
         * pass any request content in chunked form.
         */
        apr_table_mergen(to_h1->headers, "Transfer-Encoding", "chunked");
    }
    
    h2_task_set_request(task, to_h1->method, 
                        to_h1->scheme, 
                        to_h1->authority, 
                        to_h1->path, 
                        to_h1->headers, eos);
    to_h1->eoh = 1;
    
    if (eos) {
        apr_status_t status = h2_to_h1_close(to_h1);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, to_h1->m->c,
                          APLOGNO(02960) 
                          "h2_to_h1(%ld-%d): end headers, eos=%d", 
                          to_h1->m->id, to_h1->stream_id, eos);
        }
        return status;
    }
    return APR_SUCCESS;
}