int curl_dogetnameinfo(GETNAMEINFO_QUAL_ARG1 GETNAMEINFO_TYPE_ARG1 sa,
                       GETNAMEINFO_TYPE_ARG2 salen,
                       char *host, GETNAMEINFO_TYPE_ARG46 hostlen,
                       char *serv, GETNAMEINFO_TYPE_ARG46 servlen,
                       GETNAMEINFO_TYPE_ARG7 flags,
                       int line, const char *source)
{
  int res = (getnameinfo)(sa, salen,
                          host, hostlen,
                          serv, servlen,
                          flags);
  if(0 == res)
    /* success */
    curl_memlog("GETNAME %s:%d getnameinfo()\n",
                source, line);
  else
    curl_memlog("GETNAME %s:%d getnameinfo() failed = %d\n",
                source, line, res);
  return res;
}