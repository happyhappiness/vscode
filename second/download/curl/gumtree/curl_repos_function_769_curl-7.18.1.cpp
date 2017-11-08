static int multi_getsock(struct Curl_one_easy *easy,
                         curl_socket_t *socks, /* points to numsocks number
                                                 of sockets */
                         int numsocks)
{
  /* If the pipe broke, or if there's no connection left for this easy handle,
     then we MUST bail out now with no bitmask set. The no connection case can
     happen when this is called from curl_multi_remove_handle() =>
     singlesocket() => multi_getsock().
  */

  if(easy->easy_handle->state.pipe_broke ||
      !easy->easy_conn) {
    return 0;
  }

  if(easy->state > CURLM_STATE_CONNECT &&
      easy->state < CURLM_STATE_COMPLETED) {
    /* Set up ownership correctly */
    easy->easy_conn->data = easy->easy_handle;
  }

  switch(easy->state) {
  case CURLM_STATE_TOOFAST:  /* returns 0, so will not select. */
  default:
    /* this will get called with CURLM_STATE_COMPLETED when a handle is
       removed */
    return 0;

  case CURLM_STATE_WAITRESOLVE:
    return Curl_resolv_getsock(easy->easy_conn, socks, numsocks);

  case CURLM_STATE_PROTOCONNECT:
    return Curl_protocol_getsock(easy->easy_conn, socks, numsocks);

  case CURLM_STATE_DOING:
    return Curl_doing_getsock(easy->easy_conn, socks, numsocks);

  case CURLM_STATE_WAITPROXYCONNECT:
  case CURLM_STATE_WAITCONNECT:
    return waitconnect_getsock(easy->easy_conn, socks, numsocks);

  case CURLM_STATE_DO_MORE:
    return domore_getsock(easy->easy_conn, socks, numsocks);

  case CURLM_STATE_PERFORM:
  case CURLM_STATE_WAITPERFORM:
    return Curl_single_getsock(easy->easy_conn, socks, numsocks);
  }

}