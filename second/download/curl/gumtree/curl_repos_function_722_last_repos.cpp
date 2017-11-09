static int synchnet(curl_socket_t f /* socket to flush */)
{

#if defined(HAVE_IOCTLSOCKET)
  unsigned long i;
#else
  int i;
#endif
  int j = 0;
  char rbuf[PKTSIZE];
  srvr_sockaddr_union_t fromaddr;
  curl_socklen_t fromaddrlen;

  for(;;) {
#if defined(HAVE_IOCTLSOCKET)
    (void) ioctlsocket(f, FIONREAD, &i);
#else
    (void) ioctl(f, FIONREAD, &i);
#endif
    if(i) {
      j++;
#ifdef ENABLE_IPV6
      if(!use_ipv6)
#endif
        fromaddrlen = sizeof(fromaddr.sa4);
#ifdef ENABLE_IPV6
      else
        fromaddrlen = sizeof(fromaddr.sa6);
#endif
      (void) recvfrom(f, rbuf, sizeof(rbuf), 0,
                      &fromaddr.sa, &fromaddrlen);
    }
    else
      break;
  }
  return j;
}