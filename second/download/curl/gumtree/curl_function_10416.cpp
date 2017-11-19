size_t tool_header_cb(void *ptr, size_t size, size_t nmemb, void *userdata)
{
  struct HdrCbData *hdrcbdata = userdata;
  struct OutStruct *outs = hdrcbdata->outs;
  struct OutStruct *heads = hdrcbdata->heads;
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

  if(!heads->config)
    return failure;

#ifdef DEBUGBUILD
  if(size * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
    warnf(heads->config, "Header data exceeds single call write limit!\n");
    return failure;
  }
#endif

  /*
   * Write header data when curl option --dump-header (-D) is given.
   */

  if(heads->config->headerfile && heads->stream) {
    size_t rc = fwrite(ptr, size, nmemb, heads->stream);
    if(rc != cb)
      return rc;
  }

  /*
   * This callback sets the filename where output shall be written when
   * curl options --remote-name (-O) and --remote-header-name (-J) have
   * been simultaneously given and additionally server returns an HTTP
   * Content-Disposition header specifying a filename property.
   */

  if(hdrcbdata->honor_cd_filename &&
     (cb > 20) && checkprefix("Content-disposition:", str)) {
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
        outs->is_cd_filename = TRUE;
        outs->s_isreg = TRUE;
        outs->fopened = FALSE;
        outs->stream = NULL;
        hdrcbdata->honor_cd_filename = FALSE;
        break;
      }
      else
        return failure;
    }
  }

  return cb;
}