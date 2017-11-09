CURLcode Curl_http_done(struct connectdata *conn,
                        CURLcode status, bool premature)
{
  struct Curl_easy *data = conn->data;
  struct HTTP *http = data->req.protop;

  /* Clear multipass flag. If authentication isn't done yet, then it will get
   * a chance to be set back to true when we output the next auth header */
  data->state.authhost.multipass = FALSE;
  data->state.authproxy.multipass = FALSE;

  Curl_unencode_cleanup(conn);

#ifdef USE_SPNEGO
  if(data->state.proxyneg.state == GSS_AUTHSENT ||
     data->state.negotiate.state == GSS_AUTHSENT) {
    /* add forbid re-use if http-code != 401/407 as a WA only needed for
     * 401/407 that signal auth failure (empty) otherwise state will be RECV
     * with current code.
     * Do not close CONNECT_ONLY connections. */
    if((data->req.httpcode != 401) && (data->req.httpcode != 407) &&
       !data->set.connect_only)
      streamclose(conn, "Negotiate transfer completed");
    Curl_cleanup_negotiate(data);
  }
#endif

  /* set the proper values (possibly modified on POST) */
  conn->seek_func = data->set.seek_func; /* restore */
  conn->seek_client = data->set.seek_client; /* restore */

  if(!http)
    return CURLE_OK;

  if(http->send_buffer) {
    Curl_add_buffer_free(http->send_buffer);
    http->send_buffer = NULL; /* clear the pointer */
  }

  Curl_http2_done(conn, premature);

  Curl_mime_cleanpart(&http->form);

  switch(data->set.httpreq) {
  case HTTPREQ_PUT:
  case HTTPREQ_POST_FORM:
  case HTTPREQ_POST_MIME:
    data->req.bytecount = http->readbytecount + http->writebytecount;
    break;
  default:
    break;
  }

  if(status)
    return status;

  if(!premature && /* this check is pointless when DONE is called before the
                      entire operation is complete */
     !conn->bits.retry &&
     !data->set.connect_only &&
     (http->readbytecount +
      data->req.headerbytecount -
      data->req.deductheadercount) <= 0) {
    /* If this connection isn't simply closed to be retried, AND nothing was
       read from the HTTP server (that counts), this can't be right so we
       return an error here */
    failf(data, "Empty reply from server");
    return CURLE_GOT_NOTHING;
  }

  return CURLE_OK;
}