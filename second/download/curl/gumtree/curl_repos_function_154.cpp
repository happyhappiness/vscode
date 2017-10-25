static int SetHTTPrequest(HttpReq req, HttpReq *store)
{
  if((*store == HTTPREQ_UNSPEC) ||
     (*store == req)) {
    *store = req;
    return 0;
  }
  fprintf(stderr, "You can only select one HTTP request!\n");
  return 1;
}