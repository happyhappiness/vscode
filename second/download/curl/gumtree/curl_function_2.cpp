static int GetLastResponse(int sockfd, char *buf,
			   struct UrlData *data)
{
  int nread;
  int read_rc=1;
  char *ptr;
  do {
    ptr=buf;

    /* get us a full line, terminated with a newline */
    for(nread=0;
        (nread<BUFSIZE) && read_rc;
        nread++, ptr++) {
#ifdef USE_SSLEAY
      if (data->use_ssl) {
        read_rc = SSL_read(data->ssl, ptr, 1);
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

    if(data->conf & CONF_VERBOSE) {
      fputs("< ", stderr);
      fwrite(buf, 1, nread, stderr);
      fputs("\n", stderr);
    }
  } while(read_rc &&
	  (nread<4 || !lastline(buf)) );
  return nread;
}