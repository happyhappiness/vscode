 * Read everything until a newline.
 */

static
int GetLine(int sockfd, char *buf, struct connectdata *conn)
{
  size_t nread;
  int read_rc=1;
  char *ptr;
  struct UrlData *data=conn->data;

  ptr=buf;

  /* get us a full line, terminated with a newline */
  for(nread=0;
      (nread<BUFSIZE) && read_rc;
      nread++, ptr++) {
    if((CURLE_OK != Curl_read(conn, sockfd, ptr, 1, &nread)) ||
       (*ptr == '\n'))
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



/*
 * This function checks the linked list of custom HTTP headers for a particular
