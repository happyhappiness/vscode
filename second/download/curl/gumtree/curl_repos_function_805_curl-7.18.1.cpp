void Curl_infof(struct SessionHandle *data, const char *fmt, ...)
{
  if(data && data->set.verbose) {
    va_list ap;
    size_t len;
    char print_buffer[1024 + 1];
    va_start(ap, fmt);
    vsnprintf(print_buffer, 1024, fmt, ap);
    va_end(ap);
    len = strlen(print_buffer);
    Curl_debug(data, CURLINFO_TEXT, print_buffer, len, NULL);
  }
}