CURLcode Curl_tftp_done(struct connectdata *conn, CURLcode status)
{
  (void)status; /* unused */

  free(conn->proto.tftp);
  conn->proto.tftp = NULL;
  Curl_pgrsDone(conn);

  return CURLE_OK;
}