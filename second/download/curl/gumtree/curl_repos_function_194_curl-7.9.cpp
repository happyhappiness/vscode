CURLcode Curl_ftp_connect(struct connectdata *conn)
{
  /* this is FTP and no proxy */
  int nread;
  struct SessionHandle *data=conn->data;
  char *buf = data->state.buffer; /* this is our buffer */
  struct FTP *ftp;
  CURLcode result;
  int ftpcode;

  myalarm(0); /* switch off the alarm stuff */

  ftp = (struct FTP *)malloc(sizeof(struct FTP));
  if(!ftp)
    return CURLE_OUT_OF_MEMORY;

  memset(ftp, 0, sizeof(struct FTP));
  conn->proto.ftp = ftp;

  /* We always support persistant connections on ftp */
  conn->bits.close = FALSE;

  /* get some initial data into the ftp struct */
  ftp->bytecountp = &conn->bytecount;

  /* no need to duplicate them, the data struct won't change */
  ftp->user = data->state.user;
  ftp->passwd = data->state.passwd;

  if (data->set.tunnel_thru_httpproxy) {
    /* We want "seamless" FTP operations through HTTP proxy tunnel */
    result = Curl_ConnectHTTPProxyTunnel(conn, conn->firstsocket,
                                         conn->hostname, conn->remote_port);
    if(CURLE_OK != result)
      return result;
  }

  if(conn->protocol & PROT_FTPS) {
    /* FTPS is simply ftp with SSL for the control channel */
    /* now, perform the SSL initialization for this socket */
    result = Curl_SSLConnect(conn);
    if(result)
      return result;
  }


  /* The first thing we do is wait for the "220*" line: */
  nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;

  if(ftpcode != 220) {
    failf(data, "This doesn't seem like a nice ftp-server response");
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }

#ifdef KRB4
  /* if not anonymous login, try a secure login */
  if(data->set.krb4) {

    /* request data protection level (default is 'clear') */
    Curl_sec_request_prot(conn, "private");

    /* We set private first as default, in case the line below fails to
       set a valid level */
    Curl_sec_request_prot(conn, data->set.krb4_level);

    if(Curl_sec_login(conn) != 0)
      infof(data, "Logging in with password in cleartext!\n");
    else
      infof(data, "Authentication successful\n");
  }
#endif
  
  /* send USER */
  ftpsendf(conn->firstsocket, conn, "USER %s", ftp->user);

  /* wait for feedback */
  nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;

  if(ftpcode == 530) {
    /* 530 User ... access denied
       (the server denies to log the specified user) */
    failf(data, "Access denied: %s", &buf[4]);
    return CURLE_FTP_ACCESS_DENIED;
  }
  else if(ftpcode == 331) {
    /* 331 Password required for ...
       (the server requires to send the user's password too) */
    ftpsendf(conn->firstsocket, conn, "PASS %s", ftp->passwd);
    nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
    if(nread < 0)
      return CURLE_OPERATION_TIMEOUTED;

    if(ftpcode == 530) {
      /* 530 Login incorrect.
         (the username and/or the password are incorrect) */
      failf(data, "the username and/or the password are incorrect");
      return CURLE_FTP_USER_PASSWORD_INCORRECT;
    }
    else if(ftpcode == 230) {
      /* 230 User ... logged in.
         (user successfully logged in) */
        
      infof(data, "We have successfully logged in\n");
    }
    else {
      failf(data, "Odd return code after PASS");
      return CURLE_FTP_WEIRD_PASS_REPLY;
    }
  }
  else if(buf[0] == '2') {
    /* 230 User ... logged in.
       (the user logged in without password) */
    infof(data, "We have successfully logged in\n");
#ifdef KRB4
	/* we are logged in (with Kerberos)
	 * now set the requested protection level
	 */
    if(conn->sec_complete)
      Curl_sec_set_protection_level(conn);

    /* we may need to issue a KAUTH here to have access to the files
     * do it if user supplied a password
     */
    if(data->state.passwd && *data->state.passwd)
      Curl_krb_kauth(conn);
#endif
  }
  else {
    failf(data, "Odd return code after USER");
    return CURLE_FTP_WEIRD_USER_REPLY;
  }

  /* send PWD to discover our entry point */
  ftpsendf(conn->firstsocket, conn, "PWD");

  /* wait for feedback */
  nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;

  if(ftpcode == 257) {
    char *dir = (char *)malloc(nread+1);
    char *store=dir;
    char *ptr=&buf[4]; /* start on the first letter */
    
    /* Reply format is like
       257<space>"<directory-name>"<space><commentary> and the RFC959 says

       The directory name can contain any character; embedded double-quotes
       should be escaped by double-quotes (the "quote-doubling" convention).
    */
    if('\"' == *ptr) {
      /* it started good */
      ptr++;
      while(ptr && *ptr) {
        if('\"' == *ptr) {
          if('\"' == ptr[1]) {
            /* "quote-doubling" */
            *store = ptr[1];
            ptr++;
          }
          else {
            /* end of path */
            *store = '\0'; /* zero terminate */
            break; /* get out of this loop */
          }
        }
        else
          *store = *ptr;
        store++;
        ptr++;
      }
      ftp->entrypath =dir; /* remember this */
      infof(data, "Entry path is '%s'\n", ftp->entrypath);
    }
    else {
      /* couldn't get the path */
    }

  }
  else {
    /* We couldn't read the PWD response! */
  }

  return CURLE_OK;
}