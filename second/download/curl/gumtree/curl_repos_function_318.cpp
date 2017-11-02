int
Curl_os400_connect(int sd, struct sockaddr * destaddr, int addrlen)

{
  int i;
  struct sockaddr_storage laddr;

  i = convert_sockaddr(&laddr, destaddr, addrlen);

  if(i < 0)
    return -1;

  return connect(sd, (struct sockaddr *) &laddr, i);
}