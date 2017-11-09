static CURLcode ftp_do_more(struct connectdata *conn, int *completep)
{
  struct Curl_easy *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result = CURLE_OK;
  bool connected = FALSE;
  bool complete = FALSE;

  /* the ftp struct is inited in ftp_connect() */
  struct FTP *ftp = data->req.protop;

  /* if the second connection isn't done yet, wait for it */
  if(!conn->bits.tcpconnect[SECONDARYSOCKET]) {
    if(Curl_connect_ongoing(conn)) {
      /* As we're in TUNNEL_CONNECT state now, we know the proxy name and port
         aren't used so we blank their arguments. TODO: make this nicer */
      result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, NULL, 0);

      return result;
    }

    result = Curl_is_connected(conn, SECONDARYSOCKET, &connected);

    /* Ready to do more? */
    if(connected) {
      DEBUGF(infof(data, "DO-MORE connected phase starts\n"));
    }
    else {
      if(result && (ftpc->count1 == 0)) {
        *completep = -1; /* go back to DOING please */
        /* this is a EPSV connect failing, try PASV instead */
        return ftp_epsv_disable(conn);
      }
      return result;
    }
  }

  result = Curl_proxy_connect(conn, SECONDARYSOCKET);
  if(result)
    return result;

  if(CONNECT_SECONDARYSOCKET_PROXY_SSL())
    return result;

  if(conn->bits.tunnel_proxy && conn->bits.httpproxy &&
     Curl_connect_ongoing(conn))
    return result;


  if(ftpc->state) {
    /* already in a state so skip the initial commands.
       They are only done to kickstart the do_more state */
    result = ftp_multi_statemach(conn, &complete);

    *completep = (int)complete;

    /* if we got an error or if we don't wait for a data connection return
       immediately */
    if(result || (ftpc->wait_data_conn != TRUE))
      return result;

    if(ftpc->wait_data_conn)
      /* if we reach the end of the FTP state machine here, *complete will be
         TRUE but so is ftpc->wait_data_conn, which says we need to wait for
         the data connection and therefore we're not actually complete */
      *completep = 0;
  }

  if(ftp->transfer <= FTPTRANSFER_INFO) {
    /* a transfer is about to take place, or if not a file name was given
       so we'll do a SIZE on it later and then we need the right TYPE first */

    if(ftpc->wait_data_conn == TRUE) {
      bool serv_conned;

      result = ReceivedServerConnect(conn, &serv_conned);
      if(result)
        return result; /* Failed to accept data connection */

      if(serv_conned) {
        /* It looks data connection is established */
        result = AcceptServerConnect(conn);
        ftpc->wait_data_conn = FALSE;
        if(!result)
          result = InitiateTransfer(conn);

        if(result)
          return result;

        *completep = 1; /* this state is now complete when the server has
                           connected back to us */
      }
    }
    else if(data->set.upload) {
      result = ftp_nb_type(conn, data->set.prefer_ascii, FTP_STOR_TYPE);
      if(result)
        return result;

      result = ftp_multi_statemach(conn, &complete);
      if(ftpc->wait_data_conn)
        /* if we reach the end of the FTP state machine here, *complete will be
           TRUE but so is ftpc->wait_data_conn, which says we need to wait for
           the data connection and therefore we're not actually complete */
        *completep = 0;
      else
        *completep = (int)complete;
    }
    else {
      /* download */
      ftp->downloadsize = -1; /* unknown as of yet */

      result = ftp_range(conn);
      if(result)
        ;
      else if(data->set.ftp_list_only || !ftpc->file) {
        /* The specified path ends with a slash, and therefore we think this
           is a directory that is requested, use LIST. But before that we
           need to set ASCII transfer mode. */

        /* But only if a body transfer was requested. */
        if(ftp->transfer == FTPTRANSFER_BODY) {
          result = ftp_nb_type(conn, TRUE, FTP_LIST_TYPE);
          if(result)
            return result;
        }
        /* otherwise just fall through */
      }
      else {
        result = ftp_nb_type(conn, data->set.prefer_ascii, FTP_RETR_TYPE);
        if(result)
          return result;
      }

      result = ftp_multi_statemach(conn, &complete);
      *completep = (int)complete;
    }
    return result;
  }

  if(!result && (ftp->transfer != FTPTRANSFER_BODY))
    /* no data to transfer. FIX: it feels like a kludge to have this here
       too! */
    Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

  if(!ftpc->wait_data_conn) {
    /* no waiting for the data connection so this is now complete */
    *completep = 1;
    DEBUGF(infof(data, "DO-MORE phase ends with %d\n", (int)result));
  }

  return result;
}