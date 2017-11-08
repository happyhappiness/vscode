CURLcode Curl_ftpsendf(struct connectdata *conn,
                       const char *fmt, ...)
{
  ssize_t bytes_written;
  char s[SBUF_SIZE];
  size_t write_len;
  char *sptr=s;
  CURLcode res = CURLE_OK;
#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
  enum protection_level data_sec = conn->data_prot;
#endif

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(s, SBUF_SIZE-3, fmt, ap);
  va_end(ap);

  strcat(s, "\r\n"); /* append a trailing CRLF */

  bytes_written=0;
  write_len = strlen(s);

#ifdef CURL_DOES_CONVERSIONS
  res = Curl_convert_to_network(conn->data, s, write_len);
  /* Curl_convert_to_network calls failf if unsuccessful */
  if(res != CURLE_OK) {
    return(res);
  }
#endif /* CURL_DOES_CONVERSIONS */

  while(1) {
#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
    conn->data_prot = prot_cmd;
#endif
    res = Curl_write(conn, conn->sock[FIRSTSOCKET], sptr, write_len,
                     &bytes_written);
#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
    conn->data_prot = data_sec;
#endif

    if(CURLE_OK != res)
      break;

    if(conn->data->set.verbose)
      Curl_debug(conn->data, CURLINFO_HEADER_OUT,
                 sptr, (size_t)bytes_written, conn);

    if(bytes_written != (ssize_t)write_len) {
      write_len -= bytes_written;
      sptr += bytes_written;
    }
    else
      break;
  }

  return res;
}