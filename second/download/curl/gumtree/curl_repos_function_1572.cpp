static CURLcode pop3_dophase_done(struct connectdata *conn, bool connected)
{
  (void)conn;
  (void)connected;

  return CURLE_OK;
}