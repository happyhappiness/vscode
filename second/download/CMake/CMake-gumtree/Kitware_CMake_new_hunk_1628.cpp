{

  struct FTP *ftp= conn->proto.ftp;



  /* We cannot send quit unconditionally. If this connection is stale or

     bad in any way, sending quit and waiting around here will make the

     disconnect wait in vain and cause more problems than we need to.



     ftp_quit() will check the state of ftp->ctl_valid. If it's ok it

     will try to send the QUIT command, otherwise it will just return.

  */



  /* The FTP session may or may not have been allocated/setup at this point! */

  if(ftp) {

    (void)ftp_quit(conn); /* ignore errors on the QUIT */



    if(ftp->entrypath)

      free(ftp->entrypath);

    if(ftp->cache) {

      free(ftp->cache);

      ftp->cache = NULL;

    }

    freedirs(ftp);

  }

  return CURLE_OK;

}



/***********************************************************************

 *

 * ftp_mkd()

 *

 * Makes a directory on the FTP server.

 *

 * Calls failf()

 */

static CURLcode ftp_mkd(struct connectdata *conn, char *path)

{

  CURLcode result=CURLE_OK;

  int ftpcode; /* for ftp status */

  ssize_t nread;



  /* Create a directory on the remote server */

  FTPSENDF(conn, "MKD %s", path);



  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

  if(result)

    return result;



  switch(ftpcode) {

  case 257:

    /* success! */

    infof( conn->data , "Created remote directory %s\n" , path );

    break;

  case 550:

    failf(conn->data, "Permission denied to make directory %s", path);

    result = CURLE_FTP_ACCESS_DENIED;

    break;

  default:

    failf(conn->data, "unrecognized MKD response: %d", ftpcode );

    result = CURLE_FTP_ACCESS_DENIED;

    break;

  }

  return  result;

}



/***********************************************************************

 *

 * ftp_cwd()

 *

 * Send 'CWD' to the remote server to Change Working Directory.  It is the ftp

 * version of the unix 'cd' command. This function is only called from the

 * ftp_cwd_and_mkd() function these days.

 *

 * This function does NOT call failf().

 */

static

CURLcode ftp_cwd(struct connectdata *conn, char *path)

{

  ssize_t nread;

  int     ftpcode;

  CURLcode result;



  FTPSENDF(conn, "CWD %s", path);

  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

  if (!result) {

    /* According to RFC959, CWD is supposed to return 250 on success, but

       there seem to be non-compliant FTP servers out there that return 200,

       so we accept any '2xy' code here. */

    if (ftpcode/100 != 2)

      result = CURLE_FTP_ACCESS_DENIED;

  }



  return result;

}



/***********************************************************************

 *

 * ftp_cwd_and_mkd()

 *

 * Change to the given directory.  If the directory is not present, and we

 * have been told to allow it, then create the directory and cd to it.

 *

 */

static CURLcode ftp_cwd_and_mkd(struct connectdata *conn, char *path)

{

  CURLcode result;



  result = ftp_cwd(conn, path);

  if (result) {

    if(conn->data->set.ftp_create_missing_dirs) {

      result = ftp_mkd(conn, path);

      if (result)

        /* ftp_mkd() calls failf() itself */

        return result;

      result = ftp_cwd(conn, path);

    }

    if(result)

      failf(conn->data, "Couldn't cd to %s", path);

  }

  return result;

}







/***********************************************************************

 *

 * ftp_3rdparty_pretransfer()

 *

 * Preparation for 3rd party transfer.

 *

 */

static CURLcode ftp_3rdparty_pretransfer(struct connectdata *conn)

{

  CURLcode result = CURLE_OK;

  struct SessionHandle *data = conn->data;

  struct connectdata *sec_conn = conn->sec_conn;



  /* sets transfer type */

  result = ftp_transfertype(conn, data->set.ftp_ascii);

  if (result)

    return result;



  result = ftp_transfertype(sec_conn, data->set.ftp_ascii);

  if (result)

    return result;



  /* Send any PREQUOTE strings after transfer type is set? */

  if (data->set.source_prequote) {

    /* sends command(s) to source server before file transfer */

    result = ftp_sendquote(sec_conn, data->set.source_prequote);

  }

  if (!result && data->set.prequote)

    result = ftp_sendquote(conn, data->set.prequote);



  return result;

}







/***********************************************************************

 *

 * ftp_3rdparty_transfer()

 *

 * Performs 3rd party transfer.

 *

 */

static CURLcode ftp_3rdparty_transfer(struct connectdata *conn)

{

  CURLcode result = CURLE_OK;

  ssize_t nread;

  int ftpcode, ip[4], port[2];

  struct SessionHandle *data = conn->data;

  struct connectdata *sec_conn = conn->sec_conn;

  char *buf = data->state.buffer;   /* this is our buffer */

  char *str = buf;

  char pasv_port[50];

  const char *stor_cmd;

  struct connectdata *pasv_conn;

  struct connectdata *port_conn;



  if (data->set.pasvHost == CURL_TARGET_PASV) {

    pasv_conn = conn;

    port_conn = sec_conn;

  }

  else {

    pasv_conn = sec_conn;

    port_conn = conn;

  }



  /* sets the passive mode */

  FTPSENDF(pasv_conn, "%s", "PASV");

  result = Curl_GetFTPResponse(&nread, pasv_conn, &ftpcode);

  if (result) return result;

  if (ftpcode != 227) {

    failf(data, "Odd return code after PASV:%s", buf + 3);

    return CURLE_FTP_WEIRD_PASV_REPLY;

  }



  while (*str) {

    if (6 == sscanf(str, "%d,%d,%d,%d,%d,%d",

                    &ip[0], &ip[1], &ip[2], &ip[3], &port[0], &port[1]))

      break;

    str++;

  }



  if (!*str) {

    failf(pasv_conn->data, "Couldn't interpret this 227-reply: %s", buf);

    return CURLE_FTP_WEIRD_227_FORMAT;

  }



  snprintf(pasv_port, sizeof(pasv_port), "%d,%d,%d,%d,%d,%d", ip[0], ip[1],

           ip[2], ip[3], port[0], port[1]);



  /* sets data connection between remote hosts */

  FTPSENDF(port_conn, "PORT %s", pasv_port);

  result = Curl_GetFTPResponse(&nread, port_conn, &ftpcode);

  if (result)

    return result;



  if (ftpcode != 200) {

    failf(data, "PORT command attempts failed:%s", buf + 3);

    return CURLE_FTP_PORT_FAILED;

  }



  /* we might append onto the file instead of overwriting it */

  stor_cmd = data->set.ftp_append?"APPE":"STOR";



  /* transfers file between remote hosts */

  FTPSENDF(sec_conn, "RETR %s", data->set.source_path);



  if(data->set.pasvHost == CURL_TARGET_PASV) {



    result = Curl_GetFTPResponse(&nread, sec_conn, &ftpcode);

    if (result)

      return result;



    if (ftpcode != 150) {

      failf(data, "Failed RETR: %s", buf + 4);

      return CURLE_FTP_COULDNT_RETR_FILE;

    }



    result = Curl_ftpsendf(conn, "%s %s", stor_cmd, conn->path);

    if(CURLE_OK == result)

      result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

    if (result)

      return result;



    if (ftpcode != 150) {

      failf(data, "Failed FTP upload: %s", buf + 4);

      return CURLE_FTP_COULDNT_STOR_FILE;

    }



  }

  else {



    result = Curl_ftpsendf(conn, "%s %s", stor_cmd, conn->path);

    if(CURLE_OK == result)

      result = Curl_GetFTPResponse(&nread, sec_conn, &ftpcode);

    if (result)

      return result;



    if (ftpcode != 150) {

      failf(data, "Failed FTP upload: %s", buf + 4);

      return CURLE_FTP_COULDNT_STOR_FILE;

    }



    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);

    if (result)

      return result;



    if (ftpcode != 150) {

      failf(data, "Failed FTP upload: %s", buf + 4);

      return CURLE_FTP_COULDNT_STOR_FILE;

    }

  }



  return CURLE_OK;

}







/***********************************************************************

 *

 * ftp_regular_transfer()

 *

 * The input argument is already checked for validity.

 * Performs a regular transfer between local and remote hosts.

 *

 * ftp->ctl_valid starts out as FALSE, and gets set to TRUE if we reach the

 * Curl_ftp_done() function without finding any major problem.

 */

static

CURLcode ftp_regular_transfer(struct connectdata *conn)

{

  CURLcode retcode=CURLE_OK;

  bool connected=0;

  struct SessionHandle *data = conn->data;

  struct FTP *ftp;



  char *slash_pos;  /* position of the first '/' char in curpos */

  char *cur_pos=conn->path; /* current position in ppath. point at the begin

                               of next path component */



  /* the ftp struct is already inited in ftp_connect() */

  ftp = conn->proto.ftp;

  ftp->ctl_valid = FALSE;

  conn->size = -1; /* make sure this is unknown at this point */



  Curl_pgrsSetUploadCounter(data, 0);

  Curl_pgrsSetDownloadCounter(data, 0);

  Curl_pgrsSetUploadSize(data, 0);

  Curl_pgrsSetDownloadSize(data, 0);



  ftp->dirdepth = 0;

  ftp->diralloc = 5; /* default dir depth to allocate */

  ftp->dirs = (char **)malloc(ftp->diralloc * sizeof(ftp->dirs[0]));

  if(!ftp->dirs)

    return CURLE_OUT_OF_MEMORY;

  ftp->dirs[0] = NULL; /* to start with */



  /* parse the URL path into separate path components */

  while((slash_pos=strchr(cur_pos, '/'))) {

    /* 1 or 0 to indicate absolute directory */

    bool absolute_dir = (cur_pos - conn->path > 0) && (ftp->dirdepth == 0);



    /* seek out the next path component */

    if (slash_pos-cur_pos) {

      /* we skip empty path components, like "x//y" since the FTP command CWD

         requires a parameter and a non-existant parameter a) doesn't work on

         many servers and b) has no effect on the others. */

      int len = (int)(slash_pos - cur_pos + absolute_dir);

      ftp->dirs[ftp->dirdepth] = curl_unescape(cur_pos - absolute_dir, len);



      if (!ftp->dirs[ftp->dirdepth]) { /* run out of memory ... */

        failf(data, "no memory");

        freedirs(ftp);

        return CURLE_OUT_OF_MEMORY;

      }

    }

    else {

      cur_pos = slash_pos + 1; /* jump to the rest of the string */

      continue;

    }



    if(!retcode) {

      cur_pos = slash_pos + 1; /* jump to the rest of the string */

      if(++ftp->dirdepth >= ftp->diralloc) {

        /* enlarge array */

        char *bigger;

        ftp->diralloc *= 2; /* double the size each time */

        bigger = realloc(ftp->dirs, ftp->diralloc * sizeof(ftp->dirs[0]));

        if(!bigger) {

          freedirs(ftp);

          return CURLE_OUT_OF_MEMORY;

        }

        ftp->dirs = (char **)bigger;

      }

    }

  }



  ftp->file = cur_pos;  /* the rest is the file name */



  if(*ftp->file) {

    ftp->file = curl_unescape(ftp->file, 0);

    if(NULL == ftp->file) {

      freedirs(ftp);

      failf(data, "no memory");

      return CURLE_OUT_OF_MEMORY;

    }

  }

  else

    ftp->file=NULL; /* instead of point to a zero byte, we make it a NULL

                       pointer */



  retcode = ftp_perform(conn, &connected);



  if(CURLE_OK == retcode) {

    if(connected)

      retcode = Curl_ftp_nextconnect(conn);



    if(retcode && (conn->sock[SECONDARYSOCKET] != CURL_SOCKET_BAD)) {

      /* Failure detected, close the second socket if it was created already */

      sclose(conn->sock[SECONDARYSOCKET]);

      conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;

    }



    if(ftp->no_transfer)

      /* no data to transfer */

      retcode=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

    else if(!connected)

      /* since we didn't connect now, we want do_more to get called */

      conn->bits.do_more = TRUE;

  }

  else

    freedirs(ftp);



  ftp->ctl_valid = TRUE; /* seems good */



  return retcode;

}







/***********************************************************************

 *

 * ftp_3rdparty()

 *

 * The input argument is already checked for validity.

 * Performs a 3rd party transfer between two remote hosts.

 */

static CURLcode ftp_3rdparty(struct connectdata *conn)

{

  CURLcode retcode = CURLE_OK;



  conn->proto.ftp->ctl_valid = conn->sec_conn->proto.ftp->ctl_valid = TRUE;

  conn->size = conn->sec_conn->size = -1;



  retcode = ftp_3rdparty_pretransfer(conn);

  if (!retcode)

    retcode = ftp_3rdparty_transfer(conn);



  return retcode;

}



#endif /* CURL_DISABLE_FTP */
