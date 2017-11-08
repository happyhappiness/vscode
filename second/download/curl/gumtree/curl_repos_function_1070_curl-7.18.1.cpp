static ssize_t Curl_gtls_push(void *s, const void *buf, size_t len)
{
  return swrite(s, buf, len);
}