static int
convert_sockaddr(struct sockaddr_storage * dstaddr,
                                const struct sockaddr * srcaddr, int srclen)

{
  const struct sockaddr_un * srcu;
  struct sockaddr_un * dstu;
  unsigned int i;
  unsigned int dstsize;

  /* Convert a socket address into job CCSID, if needed. */

  if(!srcaddr || srclen < offsetof(struct sockaddr, sa_family) +
     sizeof srcaddr->sa_family || srclen > sizeof *dstaddr) {
    errno = EINVAL;
    return -1;
    }

  memcpy((char *) dstaddr, (char *) srcaddr, srclen);

  switch (srcaddr->sa_family) {

  case AF_UNIX:
    srcu = (const struct sockaddr_un *) srcaddr;
    dstu = (struct sockaddr_un *) dstaddr;
    dstsize = sizeof *dstaddr - offsetof(struct sockaddr_un, sun_path);
    srclen -= offsetof(struct sockaddr_un, sun_path);
    i = QadrtConvertA2E(dstu->sun_path, srcu->sun_path, dstsize - 1, srclen);
    dstu->sun_path[i] = '\0';
    i += offsetof(struct sockaddr_un, sun_path);
    srclen = i;
    }

  return srclen;
}