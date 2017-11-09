static CURLcode rtsp_setup_connection(struct connectdata *conn)
{
  struct RTSP *rtsp;

  conn->data->req.protop = rtsp = calloc(1, sizeof(struct RTSP));
  if(!rtsp)
    return CURLE_OUT_OF_MEMORY;

  return CURLE_OK;
}