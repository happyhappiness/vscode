bool Curl_none_data_pending(const struct connectdata *conn UNUSED_PARAM,
                            int connindex UNUSED_PARAM)
{
  (void)conn;
  (void)connindex;
  return 0;
}