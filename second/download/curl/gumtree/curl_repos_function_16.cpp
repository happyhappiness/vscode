int SetHTTPrequest(HttpReq req, HttpReq *store)
{
  if((*store == HTTPREQ_UNSPEC) ||
     (*store == req)) {
    *store = req;
    return CURLE_OK;
  }
  fprintf(stderr, "You can only select one HTTP request!\n");
  return CURLE_FAILED_INIT;
}