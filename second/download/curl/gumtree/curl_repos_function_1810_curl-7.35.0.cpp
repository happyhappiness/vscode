CURLcode Curl_pp_sendf(struct pingpong *pp,
                       const char *fmt, ...)
{
  CURLcode res;
  va_list ap;
  va_start(ap, fmt);

  res = Curl_pp_vsendf(pp, fmt, ap);

  va_end(ap);

  return res;
}