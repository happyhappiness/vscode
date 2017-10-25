char *if2ip(char *interface, char *buf, int buf_size)
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
    memset(&req, 0, sizeof(req));
    strcpy(req.ifr_name, interface);
    req.ifr_addr.sa_family = AF_INET;
    if (SYS_ERROR == ioctl(dummy, SIOCGIFADDR, &req, sizeof(req))) {
      return NULL;
    }
    else {
      struct in_addr in;

      struct sockaddr_in *s = (struct sockaddr_in *)&req.ifr_dstaddr;
      memcpy(&in, &(s->sin_addr.s_addr), sizeof(in));
#if defined(HAVE_INET_NTOA_R)
      ip = inet_ntoa_r(in,buf,buf_size);
#else
      ip = strncpy(buf,inet_ntoa(in),buf_size);
      ip[buf_size - 1] = 0;
#endif
    }
    close(dummy);
  }
  return ip;
}