static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *upload = (struct WriteThis *)userp;
  size_t max = size*nmemb;

  if(max < 1)
    return 0;

  if(upload->sizeleft) {
    size_t copylen = max;
    if(copylen > upload->sizeleft)
      copylen = upload->sizeleft;
    memcpy(ptr, upload->readptr, copylen);
    upload->readptr += copylen;
    upload->sizeleft -= copylen;
    return copylen;
  }

  return 0;                          /* no more data left to deliver */
}