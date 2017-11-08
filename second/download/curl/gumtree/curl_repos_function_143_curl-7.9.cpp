static
int GetLine(int sockfd, char *ptr, struct connectdata *conn)
{
  ssize_t nread;

  /* get us a full line, terminated with a newline */
  for(nread=0; (nread<BUFSIZE); nread++, ptr++) {
    if((CURLE_OK != Curl_read(conn, sockfd, ptr, 1, &nread)) ||
       (nread <= 0) || (*ptr == '\n'))
      break;
  }
  *ptr=0; /* zero terminate */
  
  return nread>0?nread:0;
}