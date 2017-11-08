apr_status_t h2_request_flush(h2_request *req)
{
    return h2_to_h1_flush(req->to_h1);
}