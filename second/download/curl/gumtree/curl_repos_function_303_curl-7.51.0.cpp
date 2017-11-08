int
Curl_gsk_environment_close(gsk_handle * my_env_handle)

{
  struct Curl_gsk_descriptor * p;
  int rc;

  if(!my_env_handle)
    return GSK_OS400_ERROR_INVALID_POINTER;
  if(!*my_env_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) *my_env_handle;
  if((rc = gsk_environment_close(&p->h)) == GSK_OK) {
    gsk_free_handle(p);
    *my_env_handle = (gsk_handle) NULL;
  }
  return rc;
}