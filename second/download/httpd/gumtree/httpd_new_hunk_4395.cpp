    }
    else {
        apr_table_setn(req->headers, "Host", req->authority);
    }

    s = apr_table_get(req->headers, "Content-Length");
    if (!s) {
        /* no content-length given */
        if (!eos) {
            /* We have not seen a content-length and have no eos,
             * simulate a chunked encoding for our HTTP/1.1 infrastructure,
             * in case we have "H2SerializeHeaders on" here
             */
            req->chunked = 1;
            apr_table_mergen(req->headers, "Transfer-Encoding", "chunked");
        }
        else if (apr_table_get(req->headers, "Content-Type")) {
            /* If we have a content-type, but already seen eos, no more
             * data will come. Signal a zero content length explicitly.
             */
            apr_table_setn(req->headers, "Content-Length", "0");
        }
    }

    return APR_SUCCESS;
}

h2_request *h2_request_clone(apr_pool_t *p, const h2_request *src)
{
    h2_request *dst = apr_pmemdup(p, src, sizeof(*dst));
    dst->method       = apr_pstrdup(p, src->method);
    dst->scheme       = apr_pstrdup(p, src->scheme);
    dst->authority    = apr_pstrdup(p, src->authority);
    dst->path         = apr_pstrdup(p, src->path);
    dst->headers      = apr_table_clone(p, src->headers);
    return dst;
}

request_rec *h2_request_create_rec(const h2_request *req, conn_rec *c)
{
    int access_status = HTTP_OK;    
    const char *rpath;
    apr_pool_t *p;
    request_rec *r;
    const char *s;

    apr_pool_create(&p, c->pool);
    apr_pool_tag(p, "request");
    r = apr_pcalloc(p, sizeof(request_rec));
    AP_READ_REQUEST_ENTRY((intptr_t)r, (uintptr_t)c);
    r->pool            = p;
    r->connection      = c;
    r->server          = c->base_server;
    
    r->user            = NULL;
    r->ap_auth_type    = NULL;
    
    r->allowed_methods = ap_make_method_list(p, 2);
    
