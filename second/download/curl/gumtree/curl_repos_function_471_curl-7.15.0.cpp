CURLcode Curl_tftp(struct connectdata *conn, bool *done)
{
  struct SessionHandle  *data = conn->data;
  tftp_state_data_t     *state = (tftp_state_data_t *)(conn->proto.tftp);
  tftp_event_t          event;
  CURLcode              code;
  int                   rc;
  struct sockaddr       fromaddr;
  socklen_t             fromlen;
  int                   check_time = 0;

  (void)done; /* prevent compiler warning */

  /* Run the TFTP State Machine */
  for(tftp_state_machine(state, TFTP_EVENT_INIT);
      state->state != TFTP_STATE_FIN;
      tftp_state_machine(state, event) ) {

    /* Wait until ready to read or timeout occurs */
    rc=Curl_select(state->sockfd, CURL_SOCKET_BAD, state->retry_time * 1000);

    if(rc == -1) {
      /* bail out */
      int error = Curl_ourerrno();
      failf(data, "%s\n", Curl_strerror(conn, error));
      event = TFTP_EVENT_ERROR;
    }
    else if (rc==0) {
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
                               0, &fromaddr, &fromlen);
      if(state->remote_addrlen==0) {
        memcpy(&state->remote_addr, &fromaddr, fromlen);
        state->remote_addrlen = fromlen;
      }

      /* The event is given by the TFTP packet time */
      event = (tftp_event_t)ntohs(state->rpacket.event);

      switch(event) {
      case TFTP_EVENT_DATA:
        Curl_client_write(data, CLIENTWRITE_BODY,
                          (char *)state->rpacket.u.data.data, state->rbytes-4);
        break;
      case TFTP_EVENT_ERROR:
        state->error = (tftp_error_t)ntohs(state->rpacket.u.error.code);
        infof(conn->data, "%s\n", (char *)state->rpacket.u.error.data);
        break;
      case TFTP_EVENT_ACK:
        break;
      case TFTP_EVENT_RRQ:
      case TFTP_EVENT_WRQ:
      default:
        failf(conn->data, "%s\n", "Internal error: Unexpected packet");
        break;
      }

      /* Update the progress meter */
      Curl_pgrsUpdate(conn);

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

  /* Tell curl we're done */
  Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);

  /* If we have encountered an error */
  if(state->error) {

    /* Translate internal error codes to curl error codes */
    switch(state->error) {
    case TFTP_ERR_NOTFOUND:
      code = CURLE_TFTP_NOTFOUND;
      break;
    case TFTP_ERR_PERM:
      code = CURLE_TFTP_PERM;
      break;
    case TFTP_ERR_DISKFULL:
      code = CURLE_TFTP_DISKFULL;
      break;
    case TFTP_ERR_ILLEGAL:
      code = CURLE_TFTP_ILLEGAL;
      break;
    case TFTP_ERR_UNKNOWNID:
      code = CURLE_TFTP_UNKNOWNID;
      break;
    case TFTP_ERR_EXISTS:
      code = CURLE_TFTP_EXISTS;
      break;
    case TFTP_ERR_NOSUCHUSER:
      code = CURLE_TFTP_NOSUCHUSER;
      break;
    case TFTP_ERR_TIMEOUT:
      code = CURLE_OPERATION_TIMEOUTED;
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