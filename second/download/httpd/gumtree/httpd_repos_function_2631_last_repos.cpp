h2_proxy_ngheader *h2_proxy_util_nghd_make_req(apr_pool_t *p, 
                                               const h2_proxy_request *req)
{
    
    h2_proxy_ngheader *ngh;
    size_t n;
    
    ap_assert(req);
    ap_assert(req->scheme);
    ap_assert(req->authority);
    ap_assert(req->path);
    ap_assert(req->method);

    n = 4;
    apr_table_do(count_header, &n, req->headers, NULL);
    
    ngh = apr_pcalloc(p, sizeof(h2_proxy_ngheader));
    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
    NV_ADD_LIT_CS(ngh, ":scheme", req->scheme);
    NV_ADD_LIT_CS(ngh, ":authority", req->authority);
    NV_ADD_LIT_CS(ngh, ":path", req->path);
    NV_ADD_LIT_CS(ngh, ":method", req->method);
    apr_table_do(add_table_header, ngh, req->headers, NULL);

    return ngh;
}