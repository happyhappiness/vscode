int
Curl_gsk_attribute_set_buffer_a(gsk_handle my_gsk_handle, GSK_BUF_ID bufID,
                                const char * buffer, int bufSize)

{
  struct Curl_gsk_descriptor * p;
  char * ebcdicbuf;
  int rc;

  if(!my_gsk_handle)
    return GSK_INVALID_HANDLE;
  if(!buffer)
    return GSK_OS400_ERROR_INVALID_POINTER;
  if(bufSize < 0)
    return GSK_ATTRIBUTE_INVALID_LENGTH;
  p = (struct Curl_gsk_descriptor *) my_gsk_handle;
  if(!bufSize)
    bufSize = strlen(buffer);
  if(!(ebcdicbuf = malloc(bufSize + 1)))
      return GSK_INSUFFICIENT_STORAGE;
  QadrtConvertA2E(ebcdicbuf, buffer, bufSize, bufSize);
  ebcdicbuf[bufSize] = '\0';
  rc = gsk_attribute_set_buffer(p->h, bufID, ebcdicbuf, bufSize);
  free(ebcdicbuf);
  return rc;
}