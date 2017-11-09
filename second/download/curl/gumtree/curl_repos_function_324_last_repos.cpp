int
Curl_gsk_secure_soc_read(gsk_handle my_session_handle, char * readBuffer,
                         int readBufSize, int * amtRead)

{
  struct Curl_gsk_descriptor * p;

  if(!my_session_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_session_handle;
  return gsk_secure_soc_read(p->h, readBuffer, readBufSize, amtRead);
}