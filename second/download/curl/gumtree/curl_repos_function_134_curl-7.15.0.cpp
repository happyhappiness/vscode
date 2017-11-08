static int synchnet(curl_socket_t f /* socket to flush */)
{
  int i, j = 0;
  char rbuf[PKTSIZE];
  struct sockaddr_in from;
  socklen_t fromlen;

  while (1) {
    (void) ioctl(f, FIONREAD, &i);
    if (i) {
      j++;
      fromlen = sizeof from;
      (void) recvfrom(f, rbuf, sizeof (rbuf), 0,
                      (struct sockaddr *)&from, &fromlen);
    }
    else
      return j;
  }
}