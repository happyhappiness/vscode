size_t metalink_write_cb(void *buffer, size_t sz, size_t nmemb,
                         void *userdata)
{
  struct OutStruct *outs = userdata;
  struct OperationConfig *config = outs->config;
  int rv;

  /*
   * Once that libcurl has called back tool_write_cb() the returned value
   * is checked against the amount that was intended to be written, if
   * it does not match then it fails with CURLE_WRITE_ERROR. So at this
   * point returning a value different from sz*nmemb indicates failure.
   */
  const size_t failure = (sz && nmemb) ? 0 : 1;

  if(!config)
    return failure;

  rv = metalink_parse_update(outs->metalink_parser, buffer, sz * nmemb);
  if(rv == 0)
    return sz * nmemb;
  else {
    fprintf(config->global->errors, "Metalink: parsing FAILED\n");
    return failure;
  }
}