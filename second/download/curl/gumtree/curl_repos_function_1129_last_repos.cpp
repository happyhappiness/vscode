static CURLcode rtsp_do(struct connectdata *conn, bool *done)
{
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_OK;
  Curl_RtspReq rtspreq = data->set.rtspreq;
  struct RTSP *rtsp = data->req.protop;
  struct HTTP *http;
  Curl_send_buffer *req_buffer;
  curl_off_t postsize = 0; /* for ANNOUNCE and SET_PARAMETER */
  curl_off_t putsize = 0; /* for ANNOUNCE and SET_PARAMETER */

  const char *p_request = NULL;
  const char *p_session_id = NULL;
  const char *p_accept = NULL;
  const char *p_accept_encoding = NULL;
  const char *p_range = NULL;
  const char *p_referrer = NULL;
  const char *p_stream_uri = NULL;
  const char *p_transport = NULL;
  const char *p_uagent = NULL;
  const char *p_proxyuserpwd = NULL;
  const char *p_userpwd = NULL;

  *done = TRUE;

  http = &(rtsp->http_wrapper);
  /* Assert that no one has changed the RTSP struct in an evil way */
  DEBUGASSERT((void *)http == (void *)rtsp);

  rtsp->CSeq_sent = data->state.rtsp_next_client_CSeq;
  rtsp->CSeq_recv = 0;

  /* Setup the 'p_request' pointer to the proper p_request string
   * Since all RTSP requests are included here, there is no need to
   * support custom requests like HTTP.
   **/
  data->set.opt_no_body = TRUE; /* most requests don't contain a body */
  switch(rtspreq) {
  default:
    failf(data, "Got invalid RTSP request");
    return CURLE_BAD_FUNCTION_ARGUMENT;
  case RTSPREQ_OPTIONS:
    p_request = "OPTIONS";
    break;
  case RTSPREQ_DESCRIBE:
    p_request = "DESCRIBE";
    data->set.opt_no_body = FALSE;
    break;
  case RTSPREQ_ANNOUNCE:
    p_request = "ANNOUNCE";
    break;
  case RTSPREQ_SETUP:
    p_request = "SETUP";
    break;
  case RTSPREQ_PLAY:
    p_request = "PLAY";
    break;
  case RTSPREQ_PAUSE:
    p_request = "PAUSE";
    break;
  case RTSPREQ_TEARDOWN:
    p_request = "TEARDOWN";
    break;
  case RTSPREQ_GET_PARAMETER:
    /* GET_PARAMETER's no_body status is determined later */
    p_request = "GET_PARAMETER";
    data->set.opt_no_body = FALSE;
    break;
  case RTSPREQ_SET_PARAMETER:
    p_request = "SET_PARAMETER";
    break;
  case RTSPREQ_RECORD:
    p_request = "RECORD";
    break;
  case RTSPREQ_RECEIVE:
    p_request = "";
    /* Treat interleaved RTP as body*/
    data->set.opt_no_body = FALSE;
    break;
  case RTSPREQ_LAST:
    failf(data, "Got invalid RTSP request: RTSPREQ_LAST");
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }

  if(rtspreq == RTSPREQ_RECEIVE) {
    Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE,
                        &http->readbytecount, -1, NULL);

    return result;
  }

  p_session_id = data->set.str[STRING_RTSP_SESSION_ID];
  if(!p_session_id &&
     (rtspreq & ~(RTSPREQ_OPTIONS | RTSPREQ_DESCRIBE | RTSPREQ_SETUP))) {
    failf(data, "Refusing to issue an RTSP request [%s] without a session ID.",
          p_request);
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }

  /* TODO: proxy? */

  /* Stream URI. Default to server '*' if not specified */
  if(data->set.str[STRING_RTSP_STREAM_URI]) {
    p_stream_uri = data->set.str[STRING_RTSP_STREAM_URI];
  }
  else {
    p_stream_uri = "*";
  }

  /* Transport Header for SETUP requests */
  p_transport = Curl_checkheaders(conn, "Transport:");
  if(rtspreq == RTSPREQ_SETUP && !p_transport) {
    /* New Transport: setting? */
    if(data->set.str[STRING_RTSP_TRANSPORT]) {
      Curl_safefree(conn->allocptr.rtsp_transport);

      conn->allocptr.rtsp_transport =
        aprintf("Transport: %s\r\n",
                data->set.str[STRING_RTSP_TRANSPORT]);
      if(!conn->allocptr.rtsp_transport)
        return CURLE_OUT_OF_MEMORY;
    }
    else {
      failf(data,
            "Refusing to issue an RTSP SETUP without a Transport: header.");
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }

    p_transport = conn->allocptr.rtsp_transport;
  }

  /* Accept Headers for DESCRIBE requests */
  if(rtspreq == RTSPREQ_DESCRIBE) {
    /* Accept Header */
    p_accept = Curl_checkheaders(conn, "Accept:")?
      NULL:"Accept: application/sdp\r\n";

    /* Accept-Encoding header */
    if(!Curl_checkheaders(conn, "Accept-Encoding:") &&
       data->set.str[STRING_ENCODING]) {
      Curl_safefree(conn->allocptr.accept_encoding);
      conn->allocptr.accept_encoding =
        aprintf("Accept-Encoding: %s\r\n", data->set.str[STRING_ENCODING]);

      if(!conn->allocptr.accept_encoding)
        return CURLE_OUT_OF_MEMORY;

      p_accept_encoding = conn->allocptr.accept_encoding;
    }
  }

  /* The User-Agent string might have been allocated in url.c already, because
     it might have been used in the proxy connect, but if we have got a header
     with the user-agent string specified, we erase the previously made string
     here. */
  if(Curl_checkheaders(conn, "User-Agent:") && conn->allocptr.uagent) {
    Curl_safefree(conn->allocptr.uagent);
    conn->allocptr.uagent = NULL;
  }
  else if(!Curl_checkheaders(conn, "User-Agent:") &&
          data->set.str[STRING_USERAGENT]) {
    p_uagent = conn->allocptr.uagent;
  }

  /* setup the authentication headers */
  result = Curl_http_output_auth(conn, p_request, p_stream_uri, FALSE);
  if(result)
    return result;

  p_proxyuserpwd = conn->allocptr.proxyuserpwd;
  p_userpwd = conn->allocptr.userpwd;

  /* Referrer */
  Curl_safefree(conn->allocptr.ref);
  if(data->change.referer && !Curl_checkheaders(conn, "Referer:"))
    conn->allocptr.ref = aprintf("Referer: %s\r\n", data->change.referer);
  else
    conn->allocptr.ref = NULL;

  p_referrer = conn->allocptr.ref;

  /*
   * Range Header
   * Only applies to PLAY, PAUSE, RECORD
   *
   * Go ahead and use the Range stuff supplied for HTTP
   */
  if(data->state.use_range &&
     (rtspreq  & (RTSPREQ_PLAY | RTSPREQ_PAUSE | RTSPREQ_RECORD))) {

    /* Check to see if there is a range set in the custom headers */
    if(!Curl_checkheaders(conn, "Range:") && data->state.range) {
      Curl_safefree(conn->allocptr.rangeline);
      conn->allocptr.rangeline = aprintf("Range: %s\r\n", data->state.range);
      p_range = conn->allocptr.rangeline;
    }
  }

  /*
   * Sanity check the custom headers
   */
  if(Curl_checkheaders(conn, "CSeq:")) {
    failf(data, "CSeq cannot be set as a custom header.");
    return CURLE_RTSP_CSEQ_ERROR;
  }
  if(Curl_checkheaders(conn, "Session:")) {
    failf(data, "Session ID cannot be set as a custom header.");
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }

  /* Initialize a dynamic send buffer */
  req_buffer = Curl_add_buffer_init();

  if(!req_buffer)
    return CURLE_OUT_OF_MEMORY;

  result =
    Curl_add_bufferf(req_buffer,
                     "%s %s RTSP/1.0\r\n" /* Request Stream-URI RTSP/1.0 */
                     "CSeq: %ld\r\n", /* CSeq */
                     p_request, p_stream_uri, rtsp->CSeq_sent);
  if(result)
    return result;

  /*
   * Rather than do a normal alloc line, keep the session_id unformatted
   * to make comparison easier
   */
  if(p_session_id) {
    result = Curl_add_bufferf(req_buffer, "Session: %s\r\n", p_session_id);
    if(result)
      return result;
  }

  /*
   * Shared HTTP-like options
   */
  result = Curl_add_bufferf(req_buffer,
                            "%s" /* transport */
                            "%s" /* accept */
                            "%s" /* accept-encoding */
                            "%s" /* range */
                            "%s" /* referrer */
                            "%s" /* user-agent */
                            "%s" /* proxyuserpwd */
                            "%s" /* userpwd */
                            ,
                            p_transport ? p_transport : "",
                            p_accept ? p_accept : "",
                            p_accept_encoding ? p_accept_encoding : "",
                            p_range ? p_range : "",
                            p_referrer ? p_referrer : "",
                            p_uagent ? p_uagent : "",
                            p_proxyuserpwd ? p_proxyuserpwd : "",
                            p_userpwd ? p_userpwd : "");

  /*
   * Free userpwd now --- cannot reuse this for Negotiate and possibly NTLM
   * with basic and digest, it will be freed anyway by the next request
   */
  Curl_safefree(conn->allocptr.userpwd);
  conn->allocptr.userpwd = NULL;

  if(result)
    return result;

  if((rtspreq == RTSPREQ_SETUP) || (rtspreq == RTSPREQ_DESCRIBE)) {
    result = Curl_add_timecondition(data, req_buffer);
    if(result)
      return result;
  }

  result = Curl_add_custom_headers(conn, FALSE, req_buffer);
  if(result)
    return result;

  if(rtspreq == RTSPREQ_ANNOUNCE ||
     rtspreq == RTSPREQ_SET_PARAMETER ||
     rtspreq == RTSPREQ_GET_PARAMETER) {

    if(data->set.upload) {
      putsize = data->state.infilesize;
      data->set.httpreq = HTTPREQ_PUT;

    }
    else {
      postsize = (data->state.infilesize != -1)?
        data->state.infilesize:
        (data->set.postfields? (curl_off_t)strlen(data->set.postfields):0);
      data->set.httpreq = HTTPREQ_POST;
    }

    if(putsize > 0 || postsize > 0) {
      /* As stated in the http comments, it is probably not wise to
       * actually set a custom Content-Length in the headers */
      if(!Curl_checkheaders(conn, "Content-Length:")) {
        result = Curl_add_bufferf(req_buffer,
            "Content-Length: %" CURL_FORMAT_CURL_OFF_T"\r\n",
            (data->set.upload ? putsize : postsize));
        if(result)
          return result;
      }

      if(rtspreq == RTSPREQ_SET_PARAMETER ||
         rtspreq == RTSPREQ_GET_PARAMETER) {
        if(!Curl_checkheaders(conn, "Content-Type:")) {
          result = Curl_add_bufferf(req_buffer,
              "Content-Type: text/parameters\r\n");
          if(result)
            return result;
        }
      }

      if(rtspreq == RTSPREQ_ANNOUNCE) {
        if(!Curl_checkheaders(conn, "Content-Type:")) {
          result = Curl_add_bufferf(req_buffer,
              "Content-Type: application/sdp\r\n");
          if(result)
            return result;
        }
      }

      data->state.expect100header = FALSE; /* RTSP posts are simple/small */
    }
    else if(rtspreq == RTSPREQ_GET_PARAMETER) {
      /* Check for an empty GET_PARAMETER (heartbeat) request */
      data->set.httpreq = HTTPREQ_HEAD;
      data->set.opt_no_body = TRUE;
    }
  }

  /* RTSP never allows chunked transfer */
  data->req.forbidchunk = TRUE;
  /* Finish the request buffer */
  result = Curl_add_buffer(req_buffer, "\r\n", 2);
  if(result)
    return result;

  if(postsize > 0) {
    result = Curl_add_buffer(req_buffer, data->set.postfields,
                             (size_t)postsize);
    if(result)
      return result;
  }

  /* issue the request */
  result = Curl_add_buffer_send(req_buffer, conn,
                                &data->info.request_size, 0, FIRSTSOCKET);
  if(result) {
    failf(data, "Failed sending RTSP request");
    return result;
  }

  Curl_setup_transfer(conn, FIRSTSOCKET, -1, TRUE, &http->readbytecount,
                      putsize?FIRSTSOCKET:-1,
                      putsize?&http->writebytecount:NULL);

  /* Increment the CSeq on success */
  data->state.rtsp_next_client_CSeq++;

  if(http->writebytecount) {
    /* if a request-body has been sent off, we make sure this progress is
       noted properly */
    Curl_pgrsSetUploadCounter(data, http->writebytecount);
    if(Curl_pgrsUpdate(conn))
      result = CURLE_ABORTED_BY_CALLBACK;
  }

  return result;
}