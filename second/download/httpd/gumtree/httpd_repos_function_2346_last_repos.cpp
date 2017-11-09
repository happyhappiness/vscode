apr_status_t h2_req_create_ngheader(h2_ngheader **ph, apr_pool_t *p, 
                                    const struct h2_request *req)
{
    
    const char *keys[] = {
        ":scheme", 
        ":authority", 
        ":path", 
        ":method", 
    };
    const char *values[] = {
        req->scheme,
        req->authority, 
        req->path, 
        req->method, 
    };
    
    ap_assert(req->scheme);
    ap_assert(req->authority);
    ap_assert(req->path);
    ap_assert(req->method);

    return ngheader_create(ph, p, 0, H2_ALEN(keys), keys, values, req->headers);
}