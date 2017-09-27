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

static apr_status_t add_h1_trailer(h2_request *req, apr_pool_t *pool, 
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
{
    char *hname, *hvalue;
    
    if (h2_req_ignore_trailer(name, nlen)) {
        return APR_SUCCESS;
    }
    
    hname = apr_pstrndup(pool, name, nlen);
    hvalue = apr_pstrndup(pool, value, vlen);
    h2_util_camel_case_header(hname, nlen);

    apr_table_mergen(req->trailers, hname, hvalue);
    
    return APR_SUCCESS;
}


apr_status_t h2_request_add_trailer(h2_request *req, apr_pool_t *pool,
                                    const char *name, size_t nlen,
                                    const char *value, size_t vlen)
{
    if (!req->trailers) {
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool, APLOGNO(03059)
                      "h2_request(%d): unanounced trailers",
                      req->id);
        return APR_EINVAL;
    }
    if (nlen == 0 || name[0] == ':') {
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool, APLOGNO(03060)
                      "h2_request(%d): pseudo header in trailer",
                      req->id);
        return APR_EINVAL;
    }
    return add_h1_trailer(req, pool, name, nlen, value, vlen);
}

h2_request *h2_request_clone(apr_pool_t *p, const h2_request *src)
{
    h2_request *dst = apr_pmemdup(p, src, sizeof(*dst));
    dst->method       = apr_pstrdup(p, src->method);
    dst->scheme       = apr_pstrdup(p, src->scheme);
    dst->authority    = apr_pstrdup(p, src->authority);
    dst->path         = apr_pstrdup(p, src->path);
    dst->headers      = apr_table_clone(p, src->headers);
    if (src->trailers) {
        dst->trailers = apr_table_clone(p, src->trailers);
    }
    return dst;
}

request_rec *h2_request_create_rec(const h2_request *req, conn_rec *conn)
{
    request_rec *r;
    apr_pool_t *p;
    int access_status = HTTP_OK;    
    
    apr_pool_create(&p, conn->pool);
    apr_pool_tag(p, "request");
    r = apr_pcalloc(p, sizeof(request_rec));
    AP_READ_REQUEST_ENTRY((intptr_t)r, (uintptr_t)conn);
    r->pool            = p;
    r->connection      = conn;
    r->server          = conn->base_server;
    
    r->user            = NULL;
    r->ap_auth_type    = NULL;
    
    r->allowed_methods = ap_make_method_list(p, 2);
    
