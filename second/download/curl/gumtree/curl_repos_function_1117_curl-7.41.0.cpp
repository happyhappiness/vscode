void curl_memlog(const char *format, ...)
{
  char *buf;
  int nchars;
  va_list ap;

  if(!logfile)
    return;

  buf = (Curl_cmalloc)(LOGLINE_BUFSIZE);
  if(!buf)
    return;

  va_start(ap, format);
  nchars = vsnprintf(buf, LOGLINE_BUFSIZE, format, ap);
  va_end(ap);

  if(nchars > LOGLINE_BUFSIZE - 1)
    nchars = LOGLINE_BUFSIZE - 1;

  if(nchars > 0)
    fwrite(buf, 1, nchars, logfile);

  (Curl_cfree)(buf);
}