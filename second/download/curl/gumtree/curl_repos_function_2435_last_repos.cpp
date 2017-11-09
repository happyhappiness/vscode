static CURLcode set_callback(struct Curl_easy *data,
                             gsk_handle h, GSK_CALLBACK_ID id, void *info)
{
  int rc = gsk_attribute_set_callback(h, id, info);

  switch(rc) {
  case GSK_OK:
    return CURLE_OK;
  case GSK_ERROR_IO:
    failf(data, "gsk_attribute_set_callback() I/O error: %s", strerror(errno));
    break;
  default:
    failf(data, "gsk_attribute_set_callback(): %s", gsk_strerror(rc));
    break;
  }
  return CURLE_SSL_CONNECT_ERROR;
}