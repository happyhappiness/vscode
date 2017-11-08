static CURLcode tftp_do(struct connectdata *conn, bool *done)
{
  struct SessionHandle  *data = conn->data;
  tftp_state_data_t     *state;
  tftp_event_t          event;
  CURLcode              code;
  int                   rc;
  struct Curl_sockaddr_storage fromaddr;
  socklen_t             fromlen;
  int                   check_time = 0;
  struct SingleRequest *k = &data->req;

  *done = TRUE;

  /*
    Since connections can be re-used between SessionHandles, this might be a
    connection already existing but on a fresh SessionHandle struct so we must
    make sure we have a good 'struct TFTP' to play with. For new connections,
    the struct TFTP is allocated and setup in the tftp_connect() function.
  */
  Curl_reset_reqproto(conn);

  if(!data->state.proto.tftp) {
    code = tftp_connect(conn, done);
    if(code)
      return code;
  }
  state = (tftp_state_data_t *)data->state.proto.tftp;

  /* Run the TFTP State Machine */
  for(code=tftp_state_machine(state, TFTP_EVENT_INIT);
      (state->state != TFTP_STATE_FIN) && (code == CURLE_OK);
      code=tftp_state_machine(state, event) ) {

    /* Wait until ready to read or timeout occurs */
    rc=Curl_socket_ready(state->sockfd, CURL_SOCKET_BAD,
                         state->retry_time * 1000);

    if(rc == -1) {
      /* bail out */
      int error = SOCKERRNO;
      failf(data, "%s", Curl_strerror(conn, error));
      event = TFTP_EVENT_ERROR;
    }
    else if(rc==0) {
      /* A timeout occured */
      event = TFTP_EVENT_TIMEOUT;

      /* Force a look at transfer timeouts */
      check_time = 0;

    }
    else {

      /* Receive the packet */
      fromlen=sizeof(fromaddr);
      state->rbytes = recvfrom(state->sockfd,
                               (void *)&state->rpacket, sizeof(state->rpacket),
                               0, (struct sockaddr *)&fromaddr, &fromlen);
      if(state->remote_addrlen==0) {
        memcpy(&state->remote_addr, &fromaddr, fromlen);
        state->remote_addrlen = fromlen;
      }

      /* Sanity check packet length */
      if(state->rbytes < 4) {
        failf(data, "Received too short packet");
        /* Not a timeout, but how best to handle it? */
        event = TFTP_EVENT_TIMEOUT;
      }
      else {

        /* The event is given by the TFTP packet time */
        event = (tftp_event_t)getrpacketevent(&state->rpacket);

        switch(event) {
        case TFTP_EVENT_DATA:
          /* Don't pass to the client empty or retransmitted packets */
          if(state->rbytes > 4 &&
              ((state->block+1) == getrpacketblock(&state->rpacket))) {
            code = Curl_client_write(conn, CLIENTWRITE_BODY,
                                     (char *)&state->rpacket.data[4],
                                     state->rbytes-4);
            if(code)
              return code;
            k->bytecount += state->rbytes-4;
            Curl_pgrsSetDownloadCounter(data, (curl_off_t) k->bytecount);
          }
          break;
        case TFTP_EVENT_ERROR:
          state->error = (tftp_error_t)getrpacketblock(&state->rpacket);
          infof(data, "%s\n", (char *)&state->rpacket.data[4]);
          break;
        case TFTP_EVENT_ACK:
          break;
        case TFTP_EVENT_RRQ:
        case TFTP_EVENT_WRQ:
        default:
          failf(data, "%s", "Internal error: Unexpected packet");
          break;
        }

        /* Update the progress meter */
        if(Curl_pgrsUpdate(conn))
          return CURLE_ABORTED_BY_CALLBACK;
      }
    }

    /* Check for transfer timeout every 10 blocks, or after timeout */
    if(check_time%10==0) {
      time_t current;
      time(&current);
      if(current>state->max_time) {
        DEBUGF(infof(data, "timeout: %d > %d\n",
                     current, state->max_time));
        state->error = TFTP_ERR_TIMEOUT;
        state->state = TFTP_STATE_FIN;
      }
    }

  }
  if(code)
    return code;

  /* Tell curl we're done */
  code = Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  if(code)
    return code;

  /* If we have encountered an error */
  if(state->error != TFTP_ERR_NONE) {

    /* Translate internal error codes to curl error codes */
    switch(state->error) {
    case TFTP_ERR_NOTFOUND:
      code = CURLE_TFTP_NOTFOUND;
      break;
    case TFTP_ERR_PERM:
      code = CURLE_TFTP_PERM;
      break;
    case TFTP_ERR_DISKFULL:
      code = CURLE_REMOTE_DISK_FULL;
      break;
    case TFTP_ERR_UNDEF:
    case TFTP_ERR_ILLEGAL:
      code = CURLE_TFTP_ILLEGAL;
      break;
    case TFTP_ERR_UNKNOWNID:
      code = CURLE_TFTP_UNKNOWNID;
      break;
    case TFTP_ERR_EXISTS:
      code = CURLE_REMOTE_FILE_EXISTS;
      break;
    case TFTP_ERR_NOSUCHUSER:
      code = CURLE_TFTP_NOSUCHUSER;
      break;
    case TFTP_ERR_TIMEOUT:
      code = CURLE_OPERATION_TIMEDOUT;
      break;
    case TFTP_ERR_NORESPONSE:
      code = CURLE_COULDNT_CONNECT;
      break;
    default:
      code= CURLE_ABORTED_BY_CALLBACK;
      break;
    }
  }
  else
    code = CURLE_OK;
  return code;
}