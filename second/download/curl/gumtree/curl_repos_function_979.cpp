static
CURLcode rtp_client_write(struct connectdata *conn, char *ptr, size_t len)
{
  struct SessionHandle *data = conn->data;
  size_t wrote;
  curl_write_callback writeit;

  if(len == 0) {
    failf (data, "Cannot write a 0 size RTP packet.");
    return CURLE_WRITE_ERROR;
  }

  writeit = data->set.fwrite_rtp?data->set.fwrite_rtp:data->set.fwrite_func;
  wrote = writeit(ptr, 1, len, data->set.rtp_out);

  if(CURL_WRITEFUNC_PAUSE == wrote) {
    failf (data, "Cannot pause RTP");
    return CURLE_WRITE_ERROR;
  }

  if(wrote != len) {
    failf (data, "Failed writing RTP data");
    return CURLE_WRITE_ERROR;
  }

  return CURLE_OK;
}