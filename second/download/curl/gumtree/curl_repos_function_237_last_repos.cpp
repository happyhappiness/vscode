static int prog_cb(void *p, double dltotal, double dlnow, double ult,
                   double uln)
{
  ConnInfo *conn = (ConnInfo *)p;

  (void)ult;
  (void)uln;

  fprintf(MSG_OUT, "\nProgress: %s (%g/%g)", conn->url, dlnow, dltotal);
  fprintf(MSG_OUT, "\nProgress: %s (%g)", conn->url, ult);

  return 0;
}