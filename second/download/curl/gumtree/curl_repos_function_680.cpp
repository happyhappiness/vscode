int curl_dogetnameinfo(const struct sockaddr *sa, socklen_t salen,
                       char *host, size_t hostlen,
                       char *serv, size_t servlen, int flags,
                       int line, const char *source)
{
  int res=(getnameinfo)(sa, salen, host, hostlen, serv, servlen, flags);
  if(0 == res) {
    /* success */
    if(logfile)
      fprintf(logfile, "GETNAME %s:%d getnameinfo()\n",
              source, line);
  }
  else {
    if(logfile)
      fprintf(logfile, "GETNAME %s:%d getnameinfo() failed = %d\n",
              source, line, res);
  }
  return res;
}