apr_status_t h2_request_close(h2_request *req)
{
    return h2_to_h1_close(req->to_h1);
}