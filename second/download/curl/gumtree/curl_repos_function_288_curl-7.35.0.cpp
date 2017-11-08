int
Curl_gsk_secure_soc_close(gsk_handle * my_session_handle)

{
  struct Curl_gsk_descriptor * p;
  int rc;

  if(!my_session_handle)
    return GSK_OS400_ERROR_INVALID_POINTER;
  if(!*my_session_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) *my_session_handle;
  if((rc = gsk_secure_soc_close(&p->h)) == GSK_OK) {
    gsk_free_handle(p);
    *my_session_handle = (gsk_handle) NULL;
  }
  return rc;
}