void Curl_infof(struct SessionHandle *data, const char *fmt, ...)
{
  va_list ap;
  if(data->set.verbose) {
    va_start(ap, fmt);
    fputs("* ", data->set.err);
    vfprintf(data->set.err, fmt, ap);
    va_end(ap);
  }
}