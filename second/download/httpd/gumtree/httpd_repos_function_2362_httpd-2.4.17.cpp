apr_status_t h2_request_write_data(h2_request *req,
                                   const char *data, size_t len)
{
    return h2_to_h1_add_data(req->to_h1, data, len);
}