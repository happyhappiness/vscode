static CURLcode set_numeric(struct Curl_easy *data,
                            gsk_handle h, GSK_NUM_ID id, int value)
{
  int rc = gsk_attribute_set_numeric_value(h, id, value);

  switch(rc) {
  case GSK_OK:
    return CURLE_OK;
  case GSK_ERROR_IO:
    failf(data, "gsk_attribute_set_numeric_value() I/O error: %s",
          strerror(errno));
    break;
  default:
    failf(data, "gsk_attribute_set_numeric_value(): %s", gsk_strerror(rc));
    break;
  }
  return CURLE_SSL_CONNECT_ERROR;
}