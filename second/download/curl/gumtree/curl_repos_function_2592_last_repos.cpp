int Curl_none_shutdown(struct connectdata *conn UNUSED_PARAM,
                       int sockindex UNUSED_PARAM)
{
  (void)conn;
  (void)sockindex;
  return 0;
}