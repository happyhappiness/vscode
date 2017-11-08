static CURLcode init_environment(struct Curl_easy *data,
                                 gsk_handle *envir, const char *appid,
                                 const char *file, const char *label,
                                 const char *password)
{
  int rc;
  CURLcode result;
  gsk_handle h;

  /* Creates the GSKit environment. */

  rc = gsk_environment_open(&h);
  switch(rc) {
  case GSK_OK:
    break;
  case GSK_INSUFFICIENT_STORAGE:
    return CURLE_OUT_OF_MEMORY;
  default:
    failf(data, "gsk_environment_open(): %s", gsk_strerror(rc));
    return CURLE_SSL_CONNECT_ERROR;
  }

  result = set_enum(data, h, GSK_SESSION_TYPE, GSK_CLIENT_SESSION, FALSE);
  if(!result && appid)
    result = set_buffer(data, h, GSK_OS400_APPLICATION_ID, appid, FALSE);
  if(!result && file)
    result = set_buffer(data, h, GSK_KEYRING_FILE, file, FALSE);
  if(!result && label)
    result = set_buffer(data, h, GSK_KEYRING_LABEL, label, FALSE);
  if(!result && password)
    result = set_buffer(data, h, GSK_KEYRING_PW, password, FALSE);

  if(!result) {
    /* Locate CAs, Client certificate and key according to our settings.
       Note: this call may be blocking for some tenths of seconds. */
    result = gskit_status(data, gsk_environment_init(h),
                          "gsk_environment_init()", CURLE_SSL_CERTPROBLEM);
    if(!result) {
      *envir = h;
      return result;
    }
  }
  /* Error: rollback. */
  gsk_environment_close(&h);
  return result;
}