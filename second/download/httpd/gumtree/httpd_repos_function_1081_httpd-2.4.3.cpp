static apr_table_t* req_err_headers_out(request_rec *r)
{
  return r->err_headers_out;
}