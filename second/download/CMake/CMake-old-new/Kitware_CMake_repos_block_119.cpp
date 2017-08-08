{
  ssize_t bytes_written;
  size_t write_len;
  char *fmt_crlf;
  char *s;
  CURLcode result;
  struct connectdata *conn = pp->conn;
  struct Curl_easy *data = conn->data;

#ifdef HAVE_GSSAPI
  enum protection_level data_sec = conn->data_prot;
#endif

  DEBUGASSERT(pp->sendleft == 0);
  DEBUGASSERT(pp->sendsize == 0);
  DEBUGASSERT(pp->sendthis == NULL);

  fmt_crlf = aprintf("%s\r\n", fmt); /* append a trailing CRLF */
  if(!fmt_crlf)
    return CURLE_OUT_OF_MEMORY;

  s = vaprintf(fmt_crlf, args); /* trailing CRLF appended */
  free(fmt_crlf);
  if(!s)
    return CURLE_OUT_OF_MEMORY;

  bytes_written = 0;
  write_len = strlen(s);

  Curl_pp_init(pp);

  result = Curl_convert_to_network(data, s, write_len);
  /* Curl_convert_to_network calls failf if unsuccessful */
  if(result) {
    free(s);
    return result;
  }

#ifdef HAVE_GSSAPI
  conn->data_prot = PROT_CMD;
#endif
  result = Curl_write(conn, conn->sock[FIRSTSOCKET], s, write_len,
                     &bytes_written);
#ifdef HAVE_GSSAPI
  DEBUGASSERT(data_sec > PROT_NONE && data_sec < PROT_LAST);
  conn->data_prot = data_sec;
#endif

  if(result) {
    free(s);
    return result;
  }

  if(conn->data->set.verbose)
    Curl_debug(conn->data, CURLINFO_HEADER_OUT,
               s, (size_t)bytes_written, conn);

  if(bytes_written != (ssize_t)write_len) {
    /* the whole chunk was not sent, keep it around and adjust sizes */
    pp->sendthis = s;
    pp->sendsize = write_len;
    pp->sendleft = write_len - bytes_written;
  }
  else {
    free(s);
    pp->sendthis = NULL;
    pp->sendleft = pp->sendsize = 0;
    pp->response = Curl_tvnow();
  }

  return CURLE_OK;
}