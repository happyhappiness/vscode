        else {
            char buffer[32];
            memset(buffer, 0, 32);
            strncpy(buffer, name, (nlen > 31)? 31 : nlen);
            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, pool,
                          APLOGNO(02954) 
                          "h2_request: ignoring unknown pseudo header %s",
                          buffer);
        }
    }
    else {
        /* non-pseudo header, append to work bucket of stream */
        status = h2_headers_add_h1(req->headers, pool, name, nlen, value, vlen);
    }
    
    return status;
}

apr_status_t h2_request_end_headers(h2_request *req, apr_pool_t *pool, int eos)
{
    const char *s;
    
    /* rfc7540, ch. 8.1.2.3:
     * - if we have :authority, it overrides any Host header 
     * - :authority MUST be ommited when converting h1->h2, so we
     *   might get a stream without, but then Host needs to be there */
    if (!req->authority) {
        const char *host = apr_table_get(req->headers, "Host");
