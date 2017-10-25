CURLcode telnet(struct connectdata *conn)
{
  struct UrlData *data = conn->data;
  int sockfd = data->firstsocket;
  fd_set readfd;
  fd_set keepfd;

  bool keepon = TRUE;
  char *buf = data->buffer;
  int nread;

  init_telnet(data);
   
  FD_ZERO (&readfd);		/* clear it */
  FD_SET (sockfd, &readfd);
  FD_SET (1, &readfd);

  keepfd = readfd;

   while (keepon)
   {
      readfd = keepfd;		/* set this every lap in the loop */

      switch (select (sockfd + 1, &readfd, NULL, NULL, NULL))
      {
      case -1:			/* error, stop reading */
	 keepon = FALSE;
	 continue;
      case 0:			/* timeout */
	 break;
      default:			/* read! */
	 if(FD_ISSET(1, &readfd))
	 {
	    nread = read(1, buf, 255);
	    telwrite(data, (unsigned char *)buf, nread);
	 }

	 if(FD_ISSET(sockfd, &readfd))
	 {
#ifndef USE_SSLEAY
	    nread = sread (sockfd, buf, BUFSIZE - 1);
#else
	    if (data->use_ssl) {
	       nread = SSL_read (data->ssl, buf, BUFSIZE - 1);
	    }
	    else {
	       nread = sread (sockfd, buf, BUFSIZE - 1);
	    }
#endif /* USE_SSLEAY */
	 }

	 /* if we receive 0 or less here, the server closed the connection and
	   we bail out from this! */
	if (nread <= 0) {
	  keepon = FALSE;
	  break;
	}

	 telrcv(data, (unsigned char *)buf, nread);
      }
   }
   return CURLE_OK;
}