static CURLcode set_enum(struct Curl_easy *data, gsk_handle h,
                GSK_ENUM_ID id, GSK_ENUM_VALUE value, bool unsupported_ok)
{
  int rc = gsk_attribute_set_enum(h, id, value);

  switch(rc) {
  case GSK_OK:
    return CURLE_OK;
  case GSK_ERROR_IO:
    failf(data, "gsk_attribute_set_enum() I/O error: %s", strerror(errno));
    break;
  case GSK_ATTRIBUTE_INVALID_ID:
    if(unsupported_ok)
      return CURLE_UNSUPPORTED_PROTOCOL;
  default:
    failf(data, "gsk_attribute_set_enum(): %s", gsk_strerror(rc));
    break;
  }
  return CURLE_SSL_CONNECT_ERROR;
}