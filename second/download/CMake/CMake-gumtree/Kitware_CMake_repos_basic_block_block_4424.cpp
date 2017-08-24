{
  struct ifreq req;
  struct in_addr in;
  struct sockaddr_in *s;
  curl_socket_t dummy;
  size_t len;

  (void)remote_scope;
  (void)remote_scope_id;

  if(!interf || (af != AF_INET))
    return IF2IP_NOT_FOUND;

  len = strlen(interf);
  if(len >= sizeof(req.ifr_name))
    return IF2IP_NOT_FOUND;

  dummy = socket(AF_INET, SOCK_STREAM, 0);
  if(CURL_SOCKET_BAD == dummy)
    return IF2IP_NOT_FOUND;

  memset(&req, 0, sizeof(req));
  memcpy(req.ifr_name, interf, len+1);
  req.ifr_addr.sa_family = AF_INET;

  if(ioctl(dummy, SIOCGIFADDR, &req) < 0) {
    sclose(dummy);
    /* With SIOCGIFADDR, we cannot tell the difference between an interface
       that does not exist and an interface that has no address of the
       correct family. Assume the interface does not exist */
    return IF2IP_NOT_FOUND;
  }

  s = (struct sockaddr_in *)(void *)&req.ifr_addr;
  memcpy(&in, &s->sin_addr, sizeof(in));
  Curl_inet_ntop(s->sin_family, &in, buf, buf_size);

  sclose(dummy);
  return IF2IP_FOUND;
}