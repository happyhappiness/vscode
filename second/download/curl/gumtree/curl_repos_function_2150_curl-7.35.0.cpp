void Curl_ssl_random(struct SessionHandle *data,
                     unsigned char *entropy,
                     size_t length)
{
  curlssl_random(data, entropy, length);
}