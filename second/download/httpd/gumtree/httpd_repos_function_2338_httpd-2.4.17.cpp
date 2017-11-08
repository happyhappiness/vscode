apr_status_t h2_to_h1_add_data(h2_to_h1 *to_h1,
                               const char *data, size_t len)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, to_h1->m->c,
                  "h2_to_h1(%ld-%d): add %ld data bytes", 
                  to_h1->m->id, to_h1->stream_id, (long)len);
    
    if (to_h1->chunked) {
        /* if input may have a body and we have not seen any
         * content-length header, we need to chunk the input data.
         */
        apr_status_t status = apr_brigade_printf(to_h1->bb, NULL, NULL,
                                                 "%lx\r\n", (unsigned long)len);
        if (status == APR_SUCCESS) {
            status = h2_to_h1_add_data_raw(to_h1, data, len);
            if (status == APR_SUCCESS) {
                status = apr_brigade_puts(to_h1->bb, NULL, NULL, "\r\n");
            }
        }
        return status;
    }
    else {
        to_h1->remain_len -= len;
        if (to_h1->remain_len < 0) {
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, to_h1->m->c,
                          APLOGNO(02961) 
                          "h2_to_h1(%ld-%d): got %ld more content bytes than announced "
                          "in content-length header: %ld", 
                          to_h1->m->id, to_h1->stream_id, 
                          (long)to_h1->content_len, -(long)to_h1->remain_len);
        }
        return h2_to_h1_add_data_raw(to_h1, data, len);
    }
}