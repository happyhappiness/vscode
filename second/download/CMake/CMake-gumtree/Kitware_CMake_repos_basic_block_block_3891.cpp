{
  RTMP *r = conn->proto.generic;

  if(!RTMP_ConnectStream(r, 0))
    return CURLE_FAILED_INIT;

  if(conn->data->set.upload) {
    Curl_pgrsSetUploadSize(conn->data, conn->data->state.infilesize);
    Curl_setup_transfer(conn, -1, -1, FALSE, NULL, FIRSTSOCKET, NULL);
  }
  else
    Curl_setup_transfer(conn, FIRSTSOCKET, -1, FALSE, NULL, -1, NULL);
  *done = TRUE;
  return CURLE_OK;
}