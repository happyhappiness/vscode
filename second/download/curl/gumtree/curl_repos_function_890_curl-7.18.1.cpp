static CURLcode ftp_statemach_act(struct connectdata *conn)
{
  CURLcode result;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  struct SessionHandle *data=conn->data;
  int ftpcode;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  static const char * const ftpauth[]  = {
    "SSL", "TLS"
  };
  size_t nread = 0;

  if(ftpc->sendleft) {
    /* we have a piece of a command still left to send */
    ssize_t written;
    result = Curl_write(conn, sock, ftpc->sendthis + ftpc->sendsize -
                        ftpc->sendleft, ftpc->sendleft, &written);
    if(result)
      return result;

    if(written != (ssize_t)ftpc->sendleft) {
      /* only a fraction was sent */
      ftpc->sendleft -= written;
    }
    else {
      free(ftpc->sendthis);
      ftpc->sendthis=NULL;
      ftpc->sendleft = ftpc->sendsize = 0;
      ftpc->response = Curl_tvnow();
    }
    return CURLE_OK;
  }

  /* we read a piece of response */
  result = ftp_readresp(sock, conn, &ftpcode, &nread);
  if(result)
    return result;

  if(ftpcode) {
    /* we have now received a full FTP server response */
    switch(ftpc->state) {
    case FTP_WAIT220:
      if(ftpcode != 220) {
        failf(data, "This doesn't seem like a nice ftp-server response");
        return CURLE_FTP_WEIRD_SERVER_REPLY;
      }

      /* We have received a 220 response fine, now we proceed. */
#if defined(HAVE_KRB4) || defined(HAVE_GSSAPI)
      if(data->set.krb) {
        /* If not anonymous login, try a secure login. Note that this
           procedure is still BLOCKING. */

        Curl_sec_request_prot(conn, "private");
        /* We set private first as default, in case the line below fails to
           set a valid level */
        Curl_sec_request_prot(conn, data->set.str[STRING_KRB_LEVEL]);

        if(Curl_sec_login(conn) != 0)
          infof(data, "Logging in with password in cleartext!\n");
        else
          infof(data, "Authentication successful\n");
      }
#endif

      if(data->set.ftp_ssl && !conn->ssl[FIRSTSOCKET].use) {
        /* We don't have a SSL/TLS connection yet, but FTPS is
           requested. Try a FTPS connection now */

        ftpc->count3=0;
        switch(data->set.ftpsslauth) {
        case CURLFTPAUTH_DEFAULT:
        case CURLFTPAUTH_SSL:
          ftpc->count2 = 1; /* add one to get next */
          ftpc->count1 = 0;
          break;
        case CURLFTPAUTH_TLS:
          ftpc->count2 = -1; /* subtract one to get next */
          ftpc->count1 = 1;
          break;
        default:
          failf(data, "unsupported parameter to CURLOPT_FTPSSLAUTH: %d",
                data->set.ftpsslauth);
          return CURLE_FAILED_INIT; /* we don't know what to do */
        }
        NBFTPSENDF(conn, "AUTH %s", ftpauth[ftpc->count1]);
        state(conn, FTP_AUTH);
      }
      else {
        result = ftp_state_user(conn);
        if(result)
          return result;
      }

      break;

    case FTP_AUTH:
      /* we have gotten the response to a previous AUTH command */

      /* RFC2228 (page 5) says:
       *
       * If the server is willing to accept the named security mechanism,
       * and does not require any security data, it must respond with
       * reply code 234/334.
       */

      if((ftpcode == 234) || (ftpcode == 334)) {
        /* Curl_ssl_connect is BLOCKING */
        result = Curl_ssl_connect(conn, FIRSTSOCKET);
        if(CURLE_OK == result) {
          conn->protocol |= PROT_FTPS;
          conn->ssl[SECONDARYSOCKET].use = FALSE; /* clear-text data */
          result = ftp_state_user(conn);
        }
      }
      else if(ftpc->count3 < 1) {
        ftpc->count3++;
        ftpc->count1 += ftpc->count2; /* get next attempt */
        result = Curl_nbftpsendf(conn, "AUTH %s", ftpauth[ftpc->count1]);
        /* remain in this same state */
      }
      else {
        if(data->set.ftp_ssl > CURLUSESSL_TRY)
          /* we failed and CURLUSESSL_CONTROL or CURLUSESSL_ALL is set */
          result = CURLE_USE_SSL_FAILED;
        else
          /* ignore the failure and continue */
          result = ftp_state_user(conn);
      }

      if(result)
        return result;
      break;

    case FTP_USER:
    case FTP_PASS:
      result = ftp_state_user_resp(conn, ftpcode, ftpc->state);
      break;

    case FTP_ACCT:
      result = ftp_state_acct_resp(conn, ftpcode);
      break;

    case FTP_PBSZ:
      /* FIX: check response code */

      /* For TLS, the data connection can have one of two security levels.

      1) Clear (requested by 'PROT C')

      2)Private (requested by 'PROT P')
      */
      if(!conn->ssl[SECONDARYSOCKET].use) {
        NBFTPSENDF(conn, "PROT %c",
                   data->set.ftp_ssl == CURLUSESSL_CONTROL ? 'C' : 'P');
        state(conn, FTP_PROT);
      }
      else {
        result = ftp_state_pwd(conn);
        if(result)
          return result;
      }

      break;

    case FTP_PROT:
      if(ftpcode/100 == 2)
        /* We have enabled SSL for the data connection! */
        conn->ssl[SECONDARYSOCKET].use =
          (bool)(data->set.ftp_ssl != CURLUSESSL_CONTROL);
      /* FTP servers typically responds with 500 if they decide to reject
         our 'P' request */
      else if(data->set.ftp_ssl > CURLUSESSL_CONTROL)
        /* we failed and bails out */
        return CURLE_USE_SSL_FAILED;

      if(data->set.ftp_ccc) {
        /* CCC - Clear Command Channel
         */
        NBFTPSENDF(conn, "CCC", NULL);
        state(conn, FTP_CCC);
      }
      else {
        result = ftp_state_pwd(conn);
        if(result)
          return result;
      }
      break;

    case FTP_CCC:
      if(ftpcode < 500) {
        /* First shut down the SSL layer (note: this call will block) */
        result = Curl_ssl_shutdown(conn, FIRSTSOCKET);

        if(result) {
          failf(conn->data, "Failed to clear the command channel (CCC)");
          return result;
        }
      }

      /* Then continue as normal */
      result = ftp_state_pwd(conn);
      if(result)
        return result;
      break;

    case FTP_PWD:
      if(ftpcode == 257) {
        char *dir = (char *)malloc(nread+1);
        char *store=dir;
        char *ptr=&data->state.buffer[4];  /* start on the first letter */

        if(!dir)
          return CURLE_OUT_OF_MEMORY;

        /* Reply format is like
           257<space>"<directory-name>"<space><commentary> and the RFC959
           says

           The directory name can contain any character; embedded
           double-quotes should be escaped by double-quotes (the
           "quote-doubling" convention).
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
          ftpc->entrypath =dir; /* remember this */
          infof(data, "Entry path is '%s'\n", ftpc->entrypath);
          /* also save it where getinfo can access it: */
          data->state.most_recent_ftp_entrypath = ftpc->entrypath;
        }
        else {
          /* couldn't get the path */
          free(dir);
          infof(data, "Failed to figure out path\n");
        }
      }
      state(conn, FTP_STOP); /* we are done with the CONNECT phase! */
      DEBUGF(infof(data, "protocol connect phase DONE\n"));
      break;

    case FTP_QUOTE:
    case FTP_POSTQUOTE:
    case FTP_RETR_PREQUOTE:
    case FTP_STOR_PREQUOTE:
      if(ftpcode >= 400) {
        failf(conn->data, "QUOT command failed with %03d", ftpcode);
        return CURLE_QUOTE_ERROR;
      }
      result = ftp_state_quote(conn, FALSE, ftpc->state);
      if(result)
        return result;

      break;

    case FTP_CWD:
      if(ftpcode/100 != 2) {
        /* failure to CWD there */
        if(conn->data->set.ftp_create_missing_dirs &&
           ftpc->count1 && !ftpc->count2) {
          /* try making it */
          ftpc->count2++; /* counter to prevent CWD-MKD loops */
          NBFTPSENDF(conn, "MKD %s", ftpc->dirs[ftpc->count1 - 1]);
          state(conn, FTP_MKD);
        }
        else {
          /* return failure */
          failf(data, "Server denied you to change to the given directory");
          ftpc->cwdfail = TRUE; /* don't remember this path as we failed
                                   to enter it */
          return CURLE_REMOTE_ACCESS_DENIED;
        }
      }
      else {
        /* success */
        ftpc->count2=0;
        if(++ftpc->count1 <= ftpc->dirdepth) {
          /* send next CWD */
          NBFTPSENDF(conn, "CWD %s", ftpc->dirs[ftpc->count1 - 1]);
        }
        else {
          result = ftp_state_post_cwd(conn);
          if(result)
            return result;
        }
      }
      break;

    case FTP_MKD:
      if(ftpcode/100 != 2) {
        /* failure to MKD the dir */
        failf(data, "Failed to MKD dir: %03d", ftpcode);
        return CURLE_REMOTE_ACCESS_DENIED;
      }
      state(conn, FTP_CWD);
      /* send CWD */
      NBFTPSENDF(conn, "CWD %s", ftpc->dirs[ftpc->count1 - 1]);
      break;

    case FTP_MDTM:
      result = ftp_state_mdtm_resp(conn, ftpcode);
      break;

    case FTP_TYPE:
    case FTP_LIST_TYPE:
    case FTP_RETR_TYPE:
    case FTP_STOR_TYPE:
      result = ftp_state_type_resp(conn, ftpcode, ftpc->state);
      break;

    case FTP_SIZE:
    case FTP_RETR_SIZE:
    case FTP_STOR_SIZE:
      result = ftp_state_size_resp(conn, ftpcode, ftpc->state);
      break;

    case FTP_REST:
    case FTP_RETR_REST:
      result = ftp_state_rest_resp(conn, ftpcode, ftpc->state);
      break;

    case FTP_PASV:
      result = ftp_state_pasv_resp(conn, ftpcode);
      break;

    case FTP_PORT:
      result = ftp_state_port_resp(conn, ftpcode);
      break;

    case FTP_LIST:
    case FTP_RETR:
      result = ftp_state_get_resp(conn, ftpcode, ftpc->state);
      break;

    case FTP_STOR:
      result = ftp_state_stor_resp(conn, ftpcode);
      break;

    case FTP_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, FTP_STOP);
      break;
    }
  } /* if(ftpcode) */

  return result;
}