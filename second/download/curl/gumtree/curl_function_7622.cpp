size_t tool_header_cb(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  struct OutStruct *outs = userdata;
  const char *str = ptr;
  const size_t cb = size * nmemb;
  const char *end = (char*)ptr + cb;

  /*
   * Once that libcurl has called back tool_header_cb() the returned value
   * is checked against the amount that was intended to be written, if
   * it does not match then it fails with CURLE_WRITE_ERROR. So at this
   * point returning a value different from sz*nmemb indicates failure.
   */
  size_t failure = (size * nmemb) ? 0 : 1;

  if(!outs->config)
    return failure;

#ifdef DEBUGBUILD
  if(size * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
    warnf(outs->config, "Header data exceeds single call write limit!\n");
    return failure;
  }
#endif

  if((cb > 20) && checkprefix("Content-disposition:", str)) {
    const char *p = str + 20;

    /* look for the 'filename=' parameter
       (encoded filenames (*=) are not supported) */
    for(;;) {
      char *filename;
      size_t len;

      while(*p && (p < end) && !ISALPHA(*p))
        p++;
      if(p > end - 9)
        break;

      if(memcmp(p, "filename=", 9)) {
        /* no match, find next parameter */
        while((p < end) && (*p != ';'))
          p++;
        continue;
      }
      p += 9;

      /* this expression below typecasts 'cb' only to avoid
         warning: signed and unsigned type in conditional expression
      */
      len = (ssize_t)cb - (p - str);
      filename = parse_filename(p, len);
      if(filename) {
        outs->filename = filename;
        outs->alloc_filename = TRUE;
        outs->s_isreg = TRUE;
        outs->fopened = FALSE;
        outs->stream = NULL;
        break;
      }
      else
        return failure;
    }
  }

  return cb;
}