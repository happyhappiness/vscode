int
Curl_gsk_attribute_get_buffer_a(gsk_handle my_gsk_handle, GSK_BUF_ID bufID,
                                const char * * buffer, int * bufSize)

{
  struct Curl_gsk_descriptor * p;
  int rc;
  const char * mybuf;
  int mylen;

  if(!my_gsk_handle)
    return GSK_INVALID_HANDLE;
  if(!buffer || !bufSize)
    return GSK_OS400_ERROR_INVALID_POINTER;
  p = (struct Curl_gsk_descriptor *) my_gsk_handle;
  if((rc = gsk_attribute_get_buffer(p->h, bufID, &mybuf, &mylen)) != GSK_OK)
    return rc;
  if((rc = cachestring(p, mybuf, mylen, buffer)) == GSK_OK)
    *bufSize = mylen;
  return rc;
}