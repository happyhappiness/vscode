char *Curl_if2ip(const char *interface, char *buf, int buf_size)
{
  int dummy;
  char *ip=NULL;

  if(!interface)
    return NULL;

  dummy = socket(AF_INET, SOCK_STREAM, 0);
  if (SYS_ERROR == dummy) {
    return NULL;
  }
  else {
    struct ifreq req;
    size_t len = strlen(interface);
    memset(&req, 0, sizeof(req));
    if(len >= sizeof(req.ifr_name))
      return NULL; /* this can't be a fine interface name */
    memcpy(req.ifr_name, interface, len+1);
    req.ifr_addr.sa_family = AF_INET;
#ifdef IOCTL_3_ARGS
    if (SYS_ERROR == ioctl(dummy, SIOCGIFADDR, &req)) {
#else
    if (SYS_ERROR == ioctl(dummy, SIOCGIFADDR, &req, sizeof(req))) {
#endif
      sclose(dummy);
      return NULL;
    }
    else {
      struct in_addr in;

      struct sockaddr_in *s = (struct sockaddr_in *)&req.ifr_dstaddr;
      memcpy(&in, &(s->sin_addr.s_addr), sizeof(in));
      ip = (char *) Curl_inet_ntop(s->sin_family, &in, buf, buf_size);
    }
    sclose(dummy);
  }
  return ip;
}

/* -- end of if2ip() -- */
#else
char *Curl_if2ip(const char *interf, char *buf, int buf_size)
{
    (void) interf;
    (void) buf;
    (void) buf_size;
    return NULL;
}