  va_start(ap, fmt);

  vsnprintf(s, 250, fmt, ap);

  va_end(ap);

  

  strcat(s, "\r\n"); /* append a trailing CRLF */



  bytes_written=0;

