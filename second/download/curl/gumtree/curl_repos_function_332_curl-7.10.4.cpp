CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  char *buf = data->state.buffer; /* this is our buffer */
  CURLcode result;
  ssize_t nread;
  int ftpcode; /* for ftp status */

  /* the ftp struct is already inited in Curl_ftp_connect() */
  struct FTP *ftp = conn->proto.ftp;
  long *bytecountp = ftp->bytecountp;

  if(data->set.upload) {

    /* Set type to binary (unless specified ASCII) */
    result = ftp_transfertype(conn, data->set.ftp_ascii);
    if(result)
      return result;

    /* Send any PREQUOTE strings after transfer type is set? (Wesley Laxton)*/
    if(data->set.prequote) {
      if ((result = ftp_sendquote(conn, data->set.prequote)) != CURLE_OK)
        return result;
    }

    if(conn->resume_from) {
      /* we're about to continue the uploading of a file */
      /* 1. get already existing file's size. We use the SIZE
         command for this which may not exist in the server!
         The SIZE command is not in RFC959. */

      /* 2. This used to set REST. But since we can do append, we
         don't another ftp command. We just skip the source file
         offset and then we APPEND the rest on the file instead */

      /* 3. pass file-size number of bytes in the source file */
      /* 4. lower the infilesize counter */
      /* => transfer as usual */

      if(conn->resume_from < 0 ) {
        /* we could've got a specified offset from the command line,
           but now we know we didn't */
        ssize_t gottensize;

        if(CURLE_OK != ftp_getsize(conn, ftp->file, &gottensize)) {
          failf(data, "Couldn't get remote file size");
          return CURLE_FTP_COULDNT_GET_SIZE;
        }
        conn->resume_from = gottensize;
      }

      if(conn->resume_from) {
        /* do we still game? */
        int passed=0;
        /* enable append instead */
        data->set.ftp_append = 1;

        /* Now, let's read off the proper amount of bytes from the
           input. If we knew it was a proper file we could've just
           fseek()ed but we only have a stream here */
        do {
          int readthisamountnow = (conn->resume_from - passed);
          int actuallyread;

          if(readthisamountnow > BUFSIZE)
            readthisamountnow = BUFSIZE;

          actuallyread =
            conn->fread(data->state.buffer, 1, readthisamountnow,
                        conn->fread_in);

          passed += actuallyread;
          if(actuallyread != readthisamountnow) {
            failf(data, "Could only read %d bytes from the input", passed);
            return CURLE_FTP_COULDNT_USE_REST;
          }
        }
        while(passed != conn->resume_from);

        /* now, decrease the size of the read */
        if(data->set.infilesize>0) {
          data->set.infilesize -= conn->resume_from;

          if(data->set.infilesize <= 0) {
            infof(data, "File already completely uploaded\n");

            /* no data to transfer */
            result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
            
            /* Set no_transfer so that we won't get any error in
             * Curl_ftp_done() because we didn't transfer anything! */
            ftp->no_transfer = TRUE; 

            return CURLE_OK;
          }
        }
        /* we've passed, proceed as normal */
      }
    }

    /* Send everything on data->state.in to the socket */
    if(data->set.ftp_append) {
      /* we append onto the file instead of rewriting it */
      FTPSENDF(conn, "APPE %s", ftp->file);
    }
    else {
      FTPSENDF(conn, "STOR %s", ftp->file);
    }

    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
    if(result)
      return result;

    if(ftpcode>=400) {
      failf(data, "Failed FTP upload:%s", buf+3);
      /* oops, we never close the sockets! */
      return CURLE_FTP_COULDNT_STOR_FILE;
    }

    if(data->set.ftp_use_port) {
      /* PORT means we are now awaiting the server to connect to us. */
      result = AllowServerConnect(data, conn, conn->secondarysocket);
      if( result )
        return result;
    }

    *bytecountp=0;

    /* When we know we're uploading a specified file, we can get the file
       size prior to the actual upload. */

    Curl_pgrsSetUploadSize(data, data->set.infilesize);

    result = Curl_Transfer(conn, -1, -1, FALSE, NULL, /* no download */
                      conn->secondarysocket, bytecountp);
    if(result)
      return result;
      
  }
  else if(!data->set.no_body) {
    /* Retrieve file or directory */
    bool dirlist=FALSE;
    long downloadsize=-1;

    if(conn->bits.use_range && conn->range) {
      long from, to;
      int totalsize=-1;
      char *ptr;
      char *ptr2;

      from=strtol(conn->range, &ptr, 0);
      while(ptr && *ptr && (isspace((int)*ptr) || (*ptr=='-')))
        ptr++;
      to=strtol(ptr, &ptr2, 0);
      if(ptr == ptr2) {
        /* we didn't get any digit */
        to=-1;
      }
      if((-1 == to) && (from>=0)) {
        /* X - */
        conn->resume_from = from;
        infof(data, "FTP RANGE %d to end of file\n", from);
      }
      else if(from < 0) {
        /* -Y */
        totalsize = -from;
        conn->maxdownload = -from;
        conn->resume_from = from;
        infof(data, "FTP RANGE the last %d bytes\n", totalsize);
      }
      else {
        /* X-Y */
        totalsize = to-from;
        conn->maxdownload = totalsize+1; /* include the last mentioned byte */
        conn->resume_from = from;
        infof(data, "FTP RANGE from %d getting %d bytes\n", from,
              conn->maxdownload);
      }
      infof(data, "range-download from %d to %d, totally %d bytes\n",
            from, to, totalsize);
      ftp->dont_check = TRUE; /* dont check for successful transfer */
    }

    if((data->set.ftp_list_only) || !ftp->file) {
      /* The specified path ends with a slash, and therefore we think this
         is a directory that is requested, use LIST. But before that we
         need to set ASCII transfer mode. */
      dirlist = TRUE;

      /* Set type to ASCII */
      result = ftp_transfertype(conn, TRUE /* ASCII enforced */);
      if(result)
        return result;

      /* if this output is to be machine-parsed, the NLST command will be
         better used since the LIST command output is not specified or
         standard in any way */

      FTPSENDF(conn, "%s",
            data->set.customrequest?data->set.customrequest:
            (data->set.ftp_list_only?"NLST":"LIST"));
    }
    else {
      ssize_t foundsize;

      /* Set type to binary (unless specified ASCII) */
      result = ftp_transfertype(conn, data->set.ftp_ascii);
      if(result)
        return result;

      /* Send any PREQUOTE strings after transfer type is set? (Wesley Laxton)*/
      if(data->set.prequote) {
        if ((result = ftp_sendquote(conn, data->set.prequote)) != CURLE_OK)
          return result;
      }

      /* Attempt to get the size, it'll be useful in some cases: for resumed
         downloads and when talking to servers that don't give away the size
         in the RETR response line. */
      result = ftp_getsize(conn, ftp->file, &foundsize);
      if(CURLE_OK == result)
        downloadsize = foundsize;

      if(conn->resume_from) {

        /* Daniel: (August 4, 1999)
         *
         * We start with trying to use the SIZE command to figure out the size
         * of the file we're gonna get. If we can get the size, this is by far
         * the best way to know if we're trying to resume beyond the EOF.
         *
         * Daniel, November 28, 2001. We *always* get the size on downloads
         * now, so it is done before this even when not doing resumes. I saved
         * the comment above for nostalgical reasons! ;-)
         */
        if(CURLE_OK != result) {
          infof(data, "ftp server doesn't support SIZE\n");
          /* We couldn't get the size and therefore we can't know if there
             really is a part of the file left to get, although the server
             will just close the connection when we start the connection so it
             won't cause us any harm, just not make us exit as nicely. */
        }
        else {
          /* We got a file size report, so we check that there actually is a
             part of the file left to get, or else we go home.  */
          if(conn->resume_from< 0) {
            /* We're supposed to download the last abs(from) bytes */
            if(foundsize < -conn->resume_from) {
              failf(data, "Offset (%d) was beyond file size (%d)",
                    conn->resume_from, foundsize);
              return CURLE_FTP_BAD_DOWNLOAD_RESUME;
            }
            /* convert to size to download */
            downloadsize = -conn->resume_from;
            /* download from where? */
            conn->resume_from = foundsize - downloadsize;
          }
          else {
            if(foundsize < conn->resume_from) {
              failf(data, "Offset (%d) was beyond file size (%d)",
                    conn->resume_from, foundsize);
              return CURLE_FTP_BAD_DOWNLOAD_RESUME;
            }
            /* Now store the number of bytes we are expected to download */
            downloadsize = foundsize-conn->resume_from;
          }
        }

        if (downloadsize == 0) {
          /* no data to transfer */
          result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
          infof(data, "File already completely downloaded\n");

          /* Set no_transfer so that we won't get any error in Curl_ftp_done()
           * because we didn't transfer the any file */
          ftp->no_transfer = TRUE;
          return CURLE_OK;
        }
	
        /* Set resume file transfer offset */
        infof(data, "Instructs server to resume from offset %d\n",
              conn->resume_from);

        FTPSENDF(conn, "REST %d", conn->resume_from);

        result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
        if(result)
          return result;

        if(ftpcode != 350) {
          failf(data, "Couldn't use REST: %s", buf+4);
          return CURLE_FTP_COULDNT_USE_REST;
        }
      }

      FTPSENDF(conn, "RETR %s", ftp->file);
    }

    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
    if(result)
      return result;

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

      int size=-1; /* default unknown size */


      /*
       * It appears that there are FTP-servers that return size 0 for files
       * when SIZE is used on the file while being in BINARY mode. To work
       * around that (stupid) behavior, we attempt to parse the RETR response
       * even if the SIZE returned size zero.
       *
       * Debugging help from Salvatore Sorrentino on February 26, 2003.
       */

      if(!dirlist &&
         !data->set.ftp_ascii &&
         (downloadsize < 1)) {
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
          int index=bytes-buf;
          /* this is a hint there is size information in there! ;-) */
          while(--index) {
            /* scan for the parenthesis and break there */
            if('(' == *bytes)
              break;
            /* if only skip digits, or else we're in deep trouble */
            if(!isdigit((int)*bytes)) {
              bytes=NULL;
              break;
            }
            /* one more estep backwards */
            bytes--;
          }
          /* only if we have nothing but digits: */
          if(bytes++) {
            /* get the number! */
            size = atoi(bytes);
          }
            
        }
      }
      else if(downloadsize > -1)
        size = downloadsize;

      if(data->set.ftp_use_port) {
        result = AllowServerConnect(data, conn, conn->secondarysocket);
        if( result )
          return result;
      }

      infof(data, "Getting file with size: %d\n", size);

      /* FTP download: */
      result=Curl_Transfer(conn, conn->secondarysocket, size, FALSE,
                           bytecountp,
                           -1, NULL); /* no upload here */
      if(result)
        return result;
    }
    else {
      failf(data, "%s", buf+4);
      return CURLE_FTP_COULDNT_RETR_FILE;
    }
	
  }
  /* end of transfer */

  return CURLE_OK;
}