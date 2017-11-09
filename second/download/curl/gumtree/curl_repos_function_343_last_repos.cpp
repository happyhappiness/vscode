int
Curl_os400_bind(int sd, struct sockaddr * localaddr, int addrlen)

{
  int i;
  struct sockaddr_storage laddr;

  i = convert_sockaddr(&laddr, localaddr, addrlen);

  if(i < 0)
    return -1;

  return bind(sd, (struct sockaddr *) &laddr, i);
}