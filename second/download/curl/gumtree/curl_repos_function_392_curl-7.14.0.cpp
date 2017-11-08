static CURLcode perhapsrewind(struct connectdata *conn)
{
  struct HTTP *http = conn->proto.http;
  struct SessionHandle *data = conn->data;
  curl_off_t bytessent;
  curl_off_t expectsend = -1; /* default is unknown */

  if(!http)
    /* If this is still NULL, we have not reach very far and we can
       safely skip this rewinding stuff */
    return CURLE_OK;

  bytessent = http->writebytecount;

  if(conn->bits.authneg)
    /* This is a state where we are known to be negotiating and we don't send
       any data then. */
    expectsend = 0;
  else {
    /* figure out how much data we are expected to send */
    switch(data->set.httpreq) {
    case HTTPREQ_POST:
      if(data->set.postfieldsize != -1)
        expectsend = data->set.postfieldsize;
      break;
    case HTTPREQ_PUT:
      if(data->set.infilesize != -1)
        expectsend = data->set.infilesize;
      break;
    case HTTPREQ_POST_FORM:
      expectsend = http->postsize;
      break;
    default:
      break;
    }
  }

  conn->bits.rewindaftersend = FALSE; /* default */

  if((expectsend == -1) || (expectsend > bytessent)) {
    /* There is still data left to send */
    if((data->state.authproxy.picked == CURLAUTH_NTLM) ||
       (data->state.authhost.picked == CURLAUTH_NTLM)) {
      if(((expectsend - bytessent) < 2000) ||
         (conn->ntlm.state != NTLMSTATE_NONE)) {
        /* The NTLM-negotiation has started *OR* there is just a little (<2K)
           data left to send, keep on sending. */

        /* rewind data when completely done sending! */
        if(!conn->bits.authneg)
          conn->bits.rewindaftersend = TRUE;

        return CURLE_OK;
      }
      if(conn->bits.close)
        /* this is already marked to get closed */
        return CURLE_OK;

      infof(data, "NTLM send, close instead of sending %ld bytes\n",
            expectsend - bytessent);
    }

    /* This is not NTLM or NTLM with many bytes left to send: close
     */
    conn->bits.close = TRUE;
    conn->size = 0; /* don't download any more than 0 bytes */
  }

  if(bytessent)
    return Curl_readrewind(conn);

  return CURLE_OK;
}