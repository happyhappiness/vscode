CURLcode Curl_ssl_random(struct Curl_easy *data,
                         unsigned char *entropy,
                         size_t length)
{
  return Curl_ssl->random(data, entropy, length);
}