  va_start(ap, fmt);
  vsnprintf(s, 250, fmt, ap);
  va_end(ap);

  if(conn->data->set.verbose)
    fprintf(conn->data->set.err, "> %s\n", s);

  strcat(s, "\r\n"); /* append a trailing CRLF */

  bytes_written=0;
