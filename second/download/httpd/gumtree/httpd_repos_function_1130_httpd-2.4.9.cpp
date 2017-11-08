static apr_table_t* req_notes(request_rec *r)
{
  return r->notes;
}