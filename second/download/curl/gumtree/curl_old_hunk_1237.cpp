
size_t tool_write_cb(char *buffer, size_t sz, size_t nmemb, void *userdata)
{
  size_t rc;
  struct OutStruct *outs = userdata;
  struct OperationConfig *config = outs->config;

  /*
   * Once that libcurl has called back tool_write_cb() the returned value
   * is checked against the amount that was intended to be written, if
   * it does not match then it fails with CURLE_WRITE_ERROR. So at this
   * point returning a value different from sz*nmemb indicates failure.
   */
  const size_t failure = (sz && nmemb) ? 0 : 1;

  if(!config)
    return failure;

#ifdef DEBUGBUILD
  if(config->include_headers) {
    if(sz * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
      warnf(config->global, "Header data size exceeds single call write "
            "limit!\n");
      return failure;
    }
  }
  else {
    if(sz * nmemb > (size_t)CURL_MAX_WRITE_SIZE) {
      warnf(config->global, "Data size exceeds single call write limit!\n");
      return failure;
    }
  }

  {
