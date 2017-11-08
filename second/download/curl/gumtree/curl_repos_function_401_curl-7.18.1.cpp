inline static ssize_t Curl_hp_recvfrom(int s, void *buf, size_t len, int flags,
                                       struct sockaddr *from,
                                       socklen_t *fromlen)
{
  ssize_t rc;
  if(fromlen) {
    int fromlen32 = *fromlen;
    rc = recvfrom(s, buf, len, flags, from, &fromlen32);
    *fromlen = fromlen32;
  }
  else {
    rc = recvfrom(s, buf, len, flags, from, 0);
  }
  return rc;
}