inline static int Curl_hp_getsockname(int s, struct sockaddr *name,
                                      socklen_t *namelen)
{
  int rc;
  if(namelen) {
     int len = *namelen;
     rc = getsockname(s, name, &len);
     *namelen = len;
   }
  else
     rc = getsockname(s, name, 0);
  return rc;
}