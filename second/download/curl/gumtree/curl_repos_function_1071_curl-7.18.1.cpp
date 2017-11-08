static ssize_t Curl_gtls_pull(void *s, void *buf, size_t len)
{
  return sread(s, buf, len);
}