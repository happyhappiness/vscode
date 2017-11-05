static apr_table_t* req_headers_out(request_rec *r)
{
    return r->headers_out;
}