int GetLine(int sockfd, char *buf, struct UrlData *data)
{
  int nread;
  int read_rc=1;
  char *ptr;
  ptr=buf;

  /* get us a full line, terminated with a newline */
  for(nread=0;
      (nread<BUFSIZE) && read_rc;
      nread++, ptr++) {
#ifdef USE_SSLEAY
    if (data->ssl.use) {
      read_rc = SSL_read(data->ssl.handle, ptr, 1);
    }
    else {
#endif
      read_rc = sread(sockfd, ptr, 1);
#ifdef USE_SSLEAY
    }
#endif /* USE_SSLEAY */
    if (*ptr == '\n')
      break;
  }
  *ptr=0; /* zero terminate */

  if(data->bits.verbose) {
    fputs("< ", data->err);
    fwrite(buf, 1, nread, data->err);
    fputs("\n", data->err);
  }
  return nread;
}