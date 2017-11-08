static CURLcode rtmp_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  (void)conn; /* unused */
  (void)status; /* unused */
  (void)premature; /* unused */

  return CURLE_OK;
}