static int synchnet(curl_socket_t f /* socket to flush */)
{

#if defined(HAVE_IOCTLSOCKET)
  unsigned long i;
#else
  int i;
#endif
  int j = 0;
  char rbuf[PKTSIZE];
  struct sockaddr_in fromaddr;
  socklen_t fromaddrlen;

  while (1) {
#if defined(HAVE_IOCTLSOCKET)
    (void) ioctlsocket(f, FIONREAD, &i);
#else
    (void) ioctl(f, FIONREAD, &i);
#endif
    if (i) {
      j++;
      fromaddrlen = sizeof fromaddr;
      (void) recvfrom(f, rbuf, sizeof (rbuf), 0,
                      (struct sockaddr *)&fromaddr, &fromaddrlen);
    }
    else
      break;
  }
  return j;
}