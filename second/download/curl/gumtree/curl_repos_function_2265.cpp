CURLcode Curl_ssl_push_certinfo(struct SessionHandle *data,
                                int certnum,
                                const char *label,
                                const char *value)
{
  size_t valuelen = strlen(value);

  return Curl_ssl_push_certinfo_len(data, certnum, label, value, valuelen);
}