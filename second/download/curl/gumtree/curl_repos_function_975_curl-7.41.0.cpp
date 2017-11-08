static CURLcode rtsp_disconnect(struct connectdata *conn, bool dead)
{
  (void) dead;
  Curl_safefree(conn->proto.rtspc.rtp_buf);
  return CURLE_OK;
}