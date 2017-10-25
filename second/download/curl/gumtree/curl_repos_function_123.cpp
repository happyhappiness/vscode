CURLcode ftp_connect(struct connectdata *conn)
{
  /* this is FTP and no proxy */
  int nread;
  struct UrlData *data=conn->data;
  char *buf = data->buffer; /* this is our buffer */
  struct FTP *ftp;

  myalarm(0); /* switch off the alarm stuff */

  ftp = (struct FTP *)malloc(sizeof(struct FTP));
  if(!ftp)
    return CURLE_OUT_OF_MEMORY;

  memset(ftp, 0, sizeof(struct FTP));
  data->proto.ftp = ftp;

  /* get some initial data into the ftp struct */
  ftp->bytecountp = &conn->bytecount;
  ftp->user = data->user;
  ftp->passwd = data->passwd;

  /* The first thing we do is wait for the "220*" line: */
  nread = GetLastResponse(data->firstsocket, buf, conn);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;
  if(strncmp(buf, "220", 3)) {
    failf(data, "This doesn't seem like a nice ftp-server response");
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }

  /* send USER */
  sendf(data->firstsocket, data, "USER %s\r\n", ftp->user);

  /* wait for feedback */
  nread = GetLastResponse(data->firstsocket, buf, conn);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;

  if(!strncmp(buf, "530", 3)) {
    /* 530 User ... access denied
       (the server denies to log the specified user) */
    failf(data, "Access denied: %s", &buf[4]);
    return CURLE_FTP_ACCESS_DENIED;
  }
  else if(!strncmp(buf, "331", 3)) {
    /* 331 Password required for ...
       (the server requires to send the user's password too) */
    sendf(data->firstsocket, data, "PASS %s\r\n", ftp->passwd);
    nread = GetLastResponse(data->firstsocket, buf, conn);
    if(nread < 0)
      return CURLE_OPERATION_TIMEOUTED;

    if(!strncmp(buf, "530", 3)) {
      /* 530 Login incorrect.
         (the username and/or the password are incorrect) */
      failf(data, "the username and/or the password are incorrect");
      return CURLE_FTP_USER_PASSWORD_INCORRECT;
    }
    else if(!strncmp(buf, "230", 3)) {
      /* 230 User ... logged in.
         (user successfully logged in) */
        
      infof(data, "We have successfully logged in\n");
    }
    else {
      failf(data, "Odd return code after PASS");
      return CURLE_FTP_WEIRD_PASS_REPLY;
    }
  }
  else if(! strncmp(buf, "230", 3)) {
    /* 230 User ... logged in.
       (the user logged in without password) */
    infof(data, "We have successfully logged in\n");
  }
  else {
    failf(data, "Odd return code after USER");
    return CURLE_FTP_WEIRD_USER_REPLY;
  }

  return CURLE_OK;
}