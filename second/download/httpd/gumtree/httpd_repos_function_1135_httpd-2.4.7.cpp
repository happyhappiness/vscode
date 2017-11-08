static apr_table_t* req_subprocess_env(request_rec *r)
{
  return r->subprocess_env;
}