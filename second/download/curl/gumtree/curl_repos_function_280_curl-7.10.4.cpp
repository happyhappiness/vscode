void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  if(data->set.errorbuffer && !data->state.errorbuf) {
    vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
    data->state.errorbuf = TRUE; /* wrote error string */

    if(data->set.verbose) {
      int len = strlen(data->set.errorbuffer);
      bool doneit=FALSE;
      if(len < CURL_ERROR_SIZE) {
        doneit = TRUE;
        data->set.errorbuffer[len] = '\n';
        data->set.errorbuffer[++len] = '\0';
      }
      Curl_debug(data, CURLINFO_TEXT, data->set.errorbuffer, len);
      if(doneit)
        /* cut off the newline again */
        data->set.errorbuffer[--len]=0;
    }
  }
  va_end(ap);
}