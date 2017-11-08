h2_ngheader *h2_util_ngheader_make_req(apr_pool_t *p, 
                                       const struct h2_request *req)
{
    
    h2_ngheader *ngh;
    size_t n;
    
    AP_DEBUG_ASSERT(req);
    AP_DEBUG_ASSERT(req->scheme);
    AP_DEBUG_ASSERT(req->authority);
    AP_DEBUG_ASSERT(req->path);
    AP_DEBUG_ASSERT(req->method);

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