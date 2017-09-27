    if (!h2_util_ignore_header(key)) {
        (*((size_t*)ctx))++;
    }
    return 1;
}

#define NV_ADD_LIT_CS(nv, k, v)     add_header(nv, k, sizeof(k) - 1, v, strlen(v))
#define NV_ADD_CS_CS(nv, k, v)      add_header(nv, k, strlen(k), v, strlen(v))

static int add_header(h2_ngheader *ngh, 
                      const char *key, size_t key_len,
                      const char *value, size_t val_len)
{
    nghttp2_nv *nv = &ngh->nv[ngh->nvlen++];
    
    nv->name = (uint8_t*)key;
    nv->namelen = key_len;
    nv->value = (uint8_t*)value;
    nv->valuelen = val_len;
    return 1;
}

static int add_table_header(void *ctx, const char *key, const char *value)
{
    if (!h2_util_ignore_header(key)) {
        add_header(ctx, key, strlen(key), value, strlen(value));
    }
    return 1;
}


h2_ngheader *h2_util_ngheader_make(apr_pool_t *p, apr_table_t *header)
{
    h2_ngheader *ngh;
    size_t n;
    
    n = 0;
    apr_table_do(count_header, &n, header, NULL);
    
    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
    apr_table_do(add_table_header, ngh, header, NULL);

    return ngh;
}

h2_ngheader *h2_util_ngheader_make_res(apr_pool_t *p, 
                                       int http_status, 
                                       apr_table_t *header)
{
    h2_ngheader *ngh;
    size_t n;
    
    n = 1;
    apr_table_do(count_header, &n, header, NULL);
    
    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
    NV_ADD_LIT_CS(ngh, ":status", apr_psprintf(p, "%d", http_status));
    apr_table_do(add_table_header, ngh, header, NULL);

    return ngh;
}

h2_ngheader *h2_util_ngheader_make_req(apr_pool_t *p, 
                                       const struct h2_request *req)
{
    
    h2_ngheader *ngh;
    size_t n;
    
    ap_assert(req);
    ap_assert(req->scheme);
    ap_assert(req->authority);
    ap_assert(req->path);
    ap_assert(req->method);

    n = 4;
    apr_table_do(count_header, &n, req->headers, NULL);
    
    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
    NV_ADD_LIT_CS(ngh, ":scheme", req->scheme);
    NV_ADD_LIT_CS(ngh, ":authority", req->authority);
    NV_ADD_LIT_CS(ngh, ":path", req->path);
    NV_ADD_LIT_CS(ngh, ":method", req->method);
    apr_table_do(add_table_header, ngh, req->headers, NULL);

    return ngh;
}

/*******************************************************************************
 * header HTTP/1 <-> HTTP/2 conversions
 ******************************************************************************/
 
