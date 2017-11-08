int
Curl_gsk_secure_soc_init(gsk_handle my_session_handle)

{
  struct Curl_gsk_descriptor * p;

  if(!my_session_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_session_handle;
  return gsk_secure_soc_init(p->h);
}