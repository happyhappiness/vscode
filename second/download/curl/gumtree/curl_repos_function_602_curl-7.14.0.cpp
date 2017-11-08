time_t curl_getdate(const char *p, const time_t *now)
{
  (void)now;
  return Curl_parsedate(p);
}