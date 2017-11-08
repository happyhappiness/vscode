inline static int Curl_hp_getsockopt(int  s, int level, int optname,
                                     void *optval, socklen_t *optlen)
{
  int rc;
  if(optlen) {
    int len = *optlen;
    rc = getsockopt(s, level, optname, optval, &len);
    *optlen = len;
  }
  else
    rc = getsockopt(s, level, optname, optval, 0);
  return rc;
}