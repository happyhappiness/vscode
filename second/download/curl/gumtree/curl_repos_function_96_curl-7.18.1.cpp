int prog_cb (void *p, double dltotal, double dlnow, double ult, double uln)
{
  ConnInfo *conn = (ConnInfo *)p;
  fprintf(MSG_OUT, "Progress: %s (%g/%g)\n", conn->url, dlnow, dltotal);
  return 0;
}