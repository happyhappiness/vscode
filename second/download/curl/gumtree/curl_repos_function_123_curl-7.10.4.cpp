CURLcode Curl_perform(struct SessionHandle *data)
{
  CURLcode res;
  CURLcode res2;
  struct connectdata *conn=NULL;
  char *newurl = NULL; /* possibly a new URL to follow to! */

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
    Curl_pgrsTime(data, TIMER_STARTSINGLE);
    res = Curl_connect(data, &conn);
    if(res == CURLE_OK) {
      res = Curl_do(&conn);

      if(res == CURLE_OK) {
        CURLcode res2; /* just a local extra result container */

        if(conn->protocol&PROT_FTPS)
          /* FTPS, disable ssl while transfering data */
          conn->ssl.use = FALSE;
        res = Transfer(conn); /* now fetch that URL please */
        if(conn->protocol&PROT_FTPS)
          /* FTPS, enable ssl again after havving transferred data */
          conn->ssl.use = TRUE;

        if(res == CURLE_OK)
          /*
           * We must duplicate the new URL here as the connection data
           * may be free()ed in the Curl_done() function.
           */
          newurl = conn->newurl?strdup(conn->newurl):NULL;
        else {
          /* The transfer phase returned error, we mark the connection to get
           * closed to prevent being re-used. This is becasue we can't
           * possibly know if the connection is in a good shape or not now. */
          conn->bits.close = TRUE;

          if(-1 !=conn->secondarysocket) {
            /* if we failed anywhere, we must clean up the secondary socket if
               it was used */
            sclose(conn->secondarysocket);
            conn->secondarysocket=-1;
          }
        }

        /* Always run Curl_done(), even if some of the previous calls
           failed, but return the previous (original) error code */
        res2 = Curl_done(conn);

        if(CURLE_OK == res)
          res = res2;
      }

      /*
       * Important: 'conn' cannot be used here, since it may have been closed
       * in 'Curl_done' or other functions.
       */

      if((res == CURLE_OK) && newurl) {
        res = Curl_follow(data, newurl);
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

  /* run post-transfer uncondionally, but don't clobber the return code if
     we already have an error code recorder */
  res2 = Curl_posttransfer(data);
  if(!res && res2)
    res = res2;

  return res;
}