static apr_status_t feed_brigade(h2_proxy_session *session, apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    apr_size_t readlen = 0;
    ssize_t n;
    
    while (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
        apr_bucket* b = APR_BRIGADE_FIRST(bb);
        
        if (APR_BUCKET_IS_METADATA(b)) {
            /* nop */
        }
        else {
            const char *bdata = NULL;
            apr_size_t blen = 0;
            
            status = apr_bucket_read(b, &bdata, &blen, APR_BLOCK_READ);
            if (status == APR_SUCCESS && blen > 0) {
                n = nghttp2_session_mem_recv(session->ngh2, (const uint8_t *)bdata, blen);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                              "h2_proxy_session(%s): feeding %ld bytes -> %ld", 
                              session->id, (long)blen, (long)n);
                if (n < 0) {
                    if (nghttp2_is_fatal((int)n)) {
                        status = APR_EGENERAL;
                    }
                }
                else {
                    readlen += n;
                    if (n < blen) {
                        apr_bucket_split(b, n);
                    }
                }
            }
        }
        apr_bucket_delete(b);
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c, 
                  "h2_proxy_session(%s): fed %ld bytes of input to session", 
                  session->id, (long)readlen);
    if (readlen == 0 && status == APR_SUCCESS) {
        return APR_EAGAIN;
    }
    return status;
}