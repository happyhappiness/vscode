int
Curl_os400_recvfrom(int sd, char * buffer, int buflen, int flags,
                                struct sockaddr * fromaddr, int * addrlen)

{
  int i;
  int rcvlen;
  int laddrlen;
  const struct sockaddr_un * srcu;
  struct sockaddr_un * dstu;
  struct sockaddr_storage laddr;

  if(!fromaddr || !addrlen || *addrlen <= 0)
    return recvfrom(sd, buffer, buflen, flags, fromaddr, addrlen);

  laddrlen = sizeof laddr;
  laddr.ss_family = AF_UNSPEC;          /* To detect if unused. */
  rcvlen = recvfrom(sd, buffer, buflen, flags,
                    (struct sockaddr *) &laddr, &laddrlen);

  if(rcvlen < 0)
    return rcvlen;

  switch (laddr.ss_family) {

  case AF_UNIX:
    srcu = (const struct sockaddr_un *) &laddr;
    dstu = (struct sockaddr_un *) fromaddr;
    i = *addrlen - offsetof(struct sockaddr_un, sun_path);
    laddrlen -= offsetof(struct sockaddr_un, sun_path);
    i = QadrtConvertE2A(dstu->sun_path, srcu->sun_path, i, laddrlen);
    laddrlen = i + offsetof(struct sockaddr_un, sun_path);

    if(laddrlen < *addrlen)
      dstu->sun_path[i] = '\0';

    break;

  case AF_UNSPEC:
    break;

  default:
    if(laddrlen > *addrlen)
      laddrlen = *addrlen;

    if(laddrlen)
      memcpy((char *) fromaddr, (char *) &laddr, laddrlen);

    break;
    }

  *addrlen = laddrlen;
  return rcvlen;
}