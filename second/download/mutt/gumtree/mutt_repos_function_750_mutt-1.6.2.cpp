static int iptostring(const struct sockaddr *addr, socklen_t addrlen,
                      char *out, unsigned outlen)
{
  char hbuf[NI_MAXHOST], pbuf[NI_MAXSERV];
  int ret;

  if (!addr || !out)
    return SASL_BADPARAM;

  ret = getnameinfo(addr, addrlen, hbuf, sizeof(hbuf), pbuf, sizeof(pbuf),
                    NI_NUMERICHOST |
#ifdef NI_WITHSCOPEID
                    NI_WITHSCOPEID |
#endif
                    NI_NUMERICSERV);
  if (ret)
    return getnameinfo_err(ret);

  if (outlen < strlen(hbuf) + strlen(pbuf) + 2)
    return SASL_BUFOVER;

  snprintf(out, outlen, "%s;%s", hbuf, pbuf);

  return SASL_OK;
}