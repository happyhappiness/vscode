static apr_status_t insert_request_line(h2_request *req, h2_mplx *m)
{
    req->to_h1 = h2_to_h1_create(req->id, req->pool, req->bucket_alloc, 
                                 req->method, 
                                 req->scheme, 
                                 req->authority, 
                                 req->path, m);
    return req->to_h1? APR_SUCCESS : APR_ENOMEM;
}