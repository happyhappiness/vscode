static size_t
Curl_formget_callback_ccsid(void * arg, const char * buf, size_t len)

{
  cfcdata * p;
  char * b;
  int l;
  size_t ret;

  p = (cfcdata *) arg;

  if((long) len <= 0)
    return (*p->append)(p->arg, buf, len);

  b = malloc(MAX_CONV_EXPANSION * len);

  if(!b)
    return (size_t) -1;

  l = convert(b, MAX_CONV_EXPANSION * len, p->ccsid, buf, len, ASCII_CCSID);

  if(l < 0) {
    free(b);
    return (size_t) -1;
    }

  ret = (*p->append)(p->arg, b, l);
  free(b);
  return ret == l? len: -1;
}