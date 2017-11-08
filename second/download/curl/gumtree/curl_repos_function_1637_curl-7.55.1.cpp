void Curl_infof(struct Curl_easy *data, const char *fmt, ...)
{
  if(data && data->set.verbose) {
    va_list ap;
    size_t len;
    char print_buffer[2048 + 1];
    va_start(ap, fmt);
    vsnprintf(print_buffer, sizeof(print_buffer), fmt, ap);
    va_end(ap);
    len = strlen(print_buffer);
    Curl_debug(data, CURLINFO_TEXT, print_buffer, len, NULL);
  }
}