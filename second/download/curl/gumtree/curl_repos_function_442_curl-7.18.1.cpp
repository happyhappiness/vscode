CURLcode Curl_perform(struct SessionHandle *data)
{
  CURLcode res;
  CURLcode res2;
  struct connectdata *conn=NULL;
  char *newurl = NULL; /* possibly a new URL to follow to! */
  bool retry = FALSE;

  data->state.used_interface = Curl_if_easy;

  res = Curl_pretransfer(data);
  if(res)
    return res;

  /*
   * It is important that there is NO 'return' from this function at any other
   * place than falling down to the end of the function! This is because we
   * have cleanup stuff that must be done before we get back, and that is only
   * performed after this do-while loop.
   */

  do {
    res = connect_host(data, &conn);   /* primary connection */

    if(res == CURLE_OK) {
      bool do_done;
      if(data->set.connect_only) {
        /* keep connection open for application to use the socket */
        conn->bits.close = FALSE;
        res = Curl_done(&conn, CURLE_OK, FALSE);
        break;
      }
      res = Curl_do(&conn, &do_done);

      if(res == CURLE_OK) {
        res = Transfer(conn); /* now fetch that URL please */
        if(res == CURLE_OK) {
          retry = Curl_retry_request(conn, &newurl);

          if(!retry)
            /*
             * We must duplicate the new URL here as the connection data may
             * be free()ed in the Curl_done() function.
             */
            newurl = data->req.newurl?strdup(data->req.newurl):NULL;
        }
        else {
          /* The transfer phase returned error, we mark the connection to get
           * closed to prevent being re-used. This is becasue we can't
           * possibly know if the connection is in a good shape or not now. */
          conn->bits.close = TRUE;

          if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET]) {
            /* if we failed anywhere, we must clean up the secondary socket if
               it was used */
            sclose(conn->sock[SECONDARYSOCKET]);
            conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
          }
        }

        /* Always run Curl_done(), even if some of the previous calls
           failed, but return the previous (original) error code */
        res2 = Curl_done(&conn, res, FALSE);

        if(CURLE_OK == res)
          res = res2;
      }
      else if(conn)
        /* Curl_do() failed, clean up left-overs in the done-call, but note
           that at some cases the conn pointer is NULL when Curl_do() failed
           and the connection cache is very small so only call Curl_done() if
           conn is still "alive".
        */
        res2 = Curl_done(&conn, res, FALSE);

      /*
       * Important: 'conn' cannot be used here, since it may have been closed
       * in 'Curl_done' or other functions.
       */

      if((res == CURLE_OK) && newurl) {
        res = Curl_follow(data, newurl, retry);
        if(CURLE_OK == res) {
          newurl = NULL;
          continue;
        }
      }
    }
    break; /* it only reaches here when this shouldn't loop */

  } while(1); /* loop if Location: */

  if(newurl)
    free(newurl);

  if(res && !data->state.errorbuf) {
    /*
     * As an extra precaution: if no error string has been set and there was
     * an error, use the strerror() string or if things are so bad that not
     * even that is good, set a bad string that mentions the error code.
     */
    const char *str = curl_easy_strerror(res);
    if(!str)
      failf(data, "unspecified error %d", (int)res);
    else
      failf(data, "%s", str);
  }

  /* run post-transfer uncondionally, but don't clobber the return code if
     we already have an error code recorder */
  res2 = Curl_posttransfer(data);
  if(!res && res2)
    res = res2;

  return res;
}