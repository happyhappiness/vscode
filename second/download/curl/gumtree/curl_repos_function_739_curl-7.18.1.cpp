static CURLcode tftp_done(struct connectdata *conn, CURLcode status,
                               bool premature)
{
  (void)status; /* unused */
  (void)premature; /* not used */

  Curl_pgrsDone(conn);

  return CURLE_OK;
}