void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  if(data->set.errorbuffer)
    vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
  va_end(ap);
}