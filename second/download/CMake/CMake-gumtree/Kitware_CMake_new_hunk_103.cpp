  return snprintf(buffer, size, "axTLS/%s", ssl_version());
}

CURLcode Curl_axtls_random(struct Curl_easy *data,
                           unsigned char *entropy,
                           size_t length)
{
  static bool ssl_seeded = FALSE;
  (void)data;
