static CURLcode set_buffer(struct Curl_easy *data, gsk_handle h,
                        GSK_BUF_ID id, const char *buffer, bool unsupported_ok)
{
  int rc = gsk_attribute_set_buffer(h, id, buffer, 0);

  switch(rc) {
  case GSK_OK:
    return CURLE_OK;
  case GSK_ERROR_IO:
    failf(data, "gsk_attribute_set_buffer() I/O error: %s", strerror(errno));
    break;
  case GSK_ATTRIBUTE_INVALID_ID:
    if(unsupported_ok)
      return CURLE_UNSUPPORTED_PROTOCOL;
  default:
    failf(data, "gsk_attribute_set_buffer(): %s", gsk_strerror(rc));
    break;
  }
  return CURLE_SSL_CONNECT_ERROR;
}