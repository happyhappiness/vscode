apr_status_t h2_request_end_headers(h2_request *req, apr_pool_t *pool, 
                                    int eos, int push)
{
    const char *s;
    
    if (req->eoh) {
        /* already done */
        return APR_SUCCESS;
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
                          "h2_request(%d): content-length value not parsed: %s",
                          req->id, s);
            return APR_EINVAL;
        }
    }
    else {
        /* no content-length given */
        req->content_length = -1;
        if (!eos) {
            /* We have not seen a content-length and have no eos,
             * simulate a chunked encoding for our HTTP/1.1 infrastructure,
             * in case we have "H2SerializeHeaders on" here
             */
            req->chunked = 1;
            apr_table_mergen(req->headers, "Transfer-Encoding", "chunked");
        }
        else if (apr_table_get(req->headers, "Content-Type")) {
            /* If we have a content-type, but already see eos, no more
             * data will come. Signal a zero content length explicitly.
             */
            apr_table_setn(req->headers, "Content-Length", "0");
        }
    }

    req->eoh = 1;
    h2_push_policy_determine(req, pool, push);
    
    /* In the presence of trailers, force behaviour of chunked encoding */
    s = apr_table_get(req->headers, "Trailer");
    if (s && s[0]) {
        req->trailers = apr_table_make(pool, 5);
        if (!req->chunked) {
            req->chunked = 1;
            apr_table_mergen(req->headers, "Transfer-Encoding", "chunked");
        }
    }
    
    return APR_SUCCESS;
}