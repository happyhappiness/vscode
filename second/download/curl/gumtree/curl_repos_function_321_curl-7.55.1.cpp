int
Curl_gsk_secure_soc_write(gsk_handle my_session_handle, char * writeBuffer,
                          int writeBufSize, int * amtWritten)

{
  struct Curl_gsk_descriptor * p;

  if(!my_session_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_session_handle;
  return gsk_secure_soc_write(p->h, writeBuffer, writeBufSize, amtWritten);
}