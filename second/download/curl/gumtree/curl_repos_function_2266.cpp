int Curl_ssl_random(struct SessionHandle *data,
                     unsigned char *entropy,
                     size_t length)
{
  return curlssl_random(data, entropy, length);
}