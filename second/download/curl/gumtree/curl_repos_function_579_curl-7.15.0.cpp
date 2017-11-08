static CURLcode ftp_state_get_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = conn->proto.ftp;
  char *buf = data->state.buffer;

  if((ftpcode == 150) || (ftpcode == 125)) {

    /*
      A;
      150 Opening BINARY mode data connection for /etc/passwd (2241
      bytes).  (ok, the file is being transfered)

      B:
      150 Opening ASCII mode data connection for /bin/ls

      C:
      150 ASCII data connection for /bin/ls (137.167.104.91,37445) (0 bytes).

      D:
      150 Opening ASCII mode data connection for /linux/fisk/kpanelrc (0.0.0.0,0) (545 bytes).

      E:
      125 Data connection already open; Transfer starting. */

    curl_off_t size=-1; /* default unknown size */


    /*
     * It appears that there are FTP-servers that return size 0 for files when
     * SIZE is used on the file while being in BINARY mode. To work around
     * that (stupid) behavior, we attempt to parse the RETR response even if
     * the SIZE returned size zero.
     *
     * Debugging help from Salvatore Sorrentino on February 26, 2003.
     */

    if((instate != FTP_LIST) &&
       !data->set.ftp_ascii &&
       (ftp->downloadsize < 1)) {
      /*
       * It seems directory listings either don't show the size or very
       * often uses size 0 anyway. ASCII transfers may very well turn out
       * that the transfered amount of data is not the same as this line
       * tells, why using this number in those cases only confuses us.
       *
       * Example D above makes this parsing a little tricky */
      char *bytes;
      bytes=strstr(buf, " bytes");
      if(bytes--) {
        long in=(long)(bytes-buf);
        /* this is a hint there is size information in there! ;-) */
        while(--in) {
          /* scan for the left parenthesis and break there */
          if('(' == *bytes)
            break;
          /* skip only digits */
          if(!isdigit((int)*bytes)) {
            bytes=NULL;
            break;
          }
          /* one more estep backwards */
          bytes--;
        }
        /* if we have nothing but digits: */
        if(bytes++) {
          /* get the number! */
          size = curlx_strtoofft(bytes, NULL, 0);
        }
      }
    }
    else if(ftp->downloadsize > -1)
      size = ftp->downloadsize;

    if(data->set.ftp_use_port) {
      /* BLOCKING */
      result = AllowServerConnect(conn);
      if( result )
        return result;
    }

    if(conn->ssl[SECONDARYSOCKET].use) {
      /* since we only have a plaintext TCP connection here, we must now
         do the TLS stuff */
      infof(data, "Doing the SSL/TLS handshake on the data stream\n");
      result = Curl_ssl_connect(conn, SECONDARYSOCKET);
      if(result)
        return result;
    }

    if(size > conn->maxdownload && conn->maxdownload > 0)
      size = conn->size = conn->maxdownload;

    if(instate != FTP_LIST)
      infof(data, "Getting file with size: %" FORMAT_OFF_T "\n", size);

    /* FTP download: */
    result=Curl_Transfer(conn, SECONDARYSOCKET, size, FALSE,
                         ftp->bytecountp,
                         -1, NULL); /* no upload here */
    if(result)
      return result;

    state(conn, FTP_STOP);
  }
  else {
    if((instate == FTP_LIST) && (ftpcode == 450)) {
      /* simply no matching files in the dir listing */
      ftp->no_transfer = TRUE; /* don't download anything */
      state(conn, FTP_STOP); /* this phase is over */
    }
    else {
      failf(data, "RETR response: %03d", ftpcode);
      return CURLE_FTP_COULDNT_RETR_FILE;
    }
  }

  return result;
}