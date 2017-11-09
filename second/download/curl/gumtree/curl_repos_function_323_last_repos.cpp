int
Curl_gsk_secure_soc_misc(gsk_handle my_session_handle, GSK_MISC_ID miscID)

{
  struct Curl_gsk_descriptor * p;

  if(!my_session_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_session_handle;
  return gsk_secure_soc_misc(p->h, miscID);
}