        status = add_h1_header(req, pool, name, nlen, value, vlen);
    }
    
    return status;
}

apr_status_t h2_request_end_headers(h2_request *req, apr_pool_t *pool, 
                                    int eos, int push)
{
    const char *s;
    
    if (req->eoh) {
        return APR_EINVAL;
    }

    /* rfc7540, ch. 8.1.2.3:
     * - if we have :authority, it overrides any Host header 
     * - :authority MUST be ommited when converting h1->h2, so we
     *   might get a stream without, but then Host needs to be there */
    if (!req->authority) {
        const char *host = apr_table_get(req->headers, "Host");
        if (!host) {
            return APR_BADARG;
        }
        req->authority = host;
    }
    else {
        apr_table_setn(req->headers, "Host", req->authority);
    }

    s = apr_table_get(req->headers, "Content-Length");
    if (s) {
        if (inspect_clen(req, s) != APR_SUCCESS) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, pool,
                          APLOGNO(02959) 
