  enum protection_level data_sec = conn->data_prot;

#endif



  va_list ap;

  va_start(ap, fmt);

  write_len = vsnprintf(s, SBUF_SIZE-3, fmt, ap);

  va_end(ap);



  strcpy(&s[write_len], "\r\n"); /* append a trailing CRLF */

  write_len +=2;

