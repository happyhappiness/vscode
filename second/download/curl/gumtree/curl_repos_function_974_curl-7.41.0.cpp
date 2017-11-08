static CURLcode rtsp_connect(struct connectdata *conn, bool *done)
{
  CURLcode httpStatus;
  struct SessionHandle *data = conn->data;

  httpStatus = Curl_http_connect(conn, done);

  /* Initialize the CSeq if not already done */
  if(data->state.rtsp_next_client_CSeq == 0)
    data->state.rtsp_next_client_CSeq = 1;
  if(data->state.rtsp_next_server_CSeq == 0)
    data->state.rtsp_next_server_CSeq = 1;

  conn->proto.rtspc.rtp_channel = -1;

  return httpStatus;
}