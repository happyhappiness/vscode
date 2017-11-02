int
Curl_os400_sendto(int sd, char * buffer, int buflen, int flags,
                                struct sockaddr * dstaddr, int addrlen)

{
  int i;
  struct sockaddr_storage laddr;

  i = convert_sockaddr(&laddr, dstaddr, addrlen);

  if(i < 0)
    return -1;

  return sendto(sd, buffer, buflen, flags, (struct sockaddr *) &laddr, i);
}