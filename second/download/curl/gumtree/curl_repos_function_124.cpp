CURLcode ftp_done(struct connectdata *conn)
{
  struct UrlData *data = conn->data;
  struct FTP *ftp = data->proto.ftp;
  size_t nread;
  char *buf = data->buffer; /* this is our buffer */
  struct curl_slist *qitem; /* QUOTE item */

  if(data->bits.upload) {
    if((-1 != data->infilesize) && (data->infilesize != *ftp->bytecountp)) {
      failf(data, "Wrote only partial file (%d out of %d bytes)",
            *ftp->bytecountp, data->infilesize);
      return CURLE_PARTIAL_FILE;
    }
  }
  else {
    if((-1 != conn->size) && (conn->size != *ftp->bytecountp) &&
       (data->maxdownload != *ftp->bytecountp)) {
      failf(data, "Received only partial file");
      return CURLE_PARTIAL_FILE;
    }
    else if(0 == *ftp->bytecountp) {
      failf(data, "No data was received!");
      return CURLE_FTP_COULDNT_RETR_FILE;
    }
  }
  /* shut down the socket to inform the server we're done */
  sclose(data->secondarysocket);
  data->secondarysocket = -1;
    
  /* now let's see what the server says about the transfer we
     just performed: */
  nread = GetLastResponse(data->firstsocket, buf, conn);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;

  /* 226 Transfer complete, 250 Requested file action okay, completed. */
  if(!strncmp(buf, "226", 3) && !strncmp(buf, "250", 3)) {
    failf(data, "%s", buf+4);
    return CURLE_FTP_WRITE_ERROR;
  }

  /* Send any post-transfer QUOTE strings? */
  if(data->postquote) {
    qitem = data->postquote;
    /* Send all QUOTE strings in same order as on command-line */
    while (qitem) {
      /* Send string */
      if (qitem->data) {
        sendf(data->firstsocket, data, "%s\r\n", qitem->data);

        nread = GetLastResponse(data->firstsocket, buf, conn);
        if(nread < 0)
          return CURLE_OPERATION_TIMEOUTED;

        if (buf[0] != '2') {
          failf(data, "QUOT string not accepted: %s",
                qitem->data);
          return CURLE_FTP_QUOTE_ERROR;
        }
      }
      qitem = qitem->next;
    }
  }

  if(ftp->file)
    free(ftp->file);
  if(ftp->dir)
    free(ftp->dir);

  /* TBD: the ftp struct is still allocated here */

  return CURLE_OK;
}