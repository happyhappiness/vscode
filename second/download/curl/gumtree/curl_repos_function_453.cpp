CURLMcode curl_multi_fdset(CURLM *multi_handle,
                           fd_set *read_fd_set, fd_set *write_fd_set,
                           fd_set *exc_fd_set, int *max_fd)
{
  /* Scan through all the easy handles to get the file descriptors set.
     Some easy handles may not have connected to the remote host yet,
     and then we must make sure that is done. */
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  int this_max_fd=-1;

  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  *max_fd = -1; /* so far none! */

  easy=multi->easy.next;
  while(easy) {
    switch(easy->state) {
    default:
      break;
    case CURLM_STATE_WAITRESOLVE:
      /* waiting for a resolve to complete */
      Curl_resolv_fdset(easy->easy_conn, read_fd_set, write_fd_set,
                        &this_max_fd);
      if(this_max_fd > *max_fd)
        *max_fd = this_max_fd;
      break;

    case CURLM_STATE_PROTOCONNECT:
      Curl_protocol_fdset(easy->easy_conn, read_fd_set, write_fd_set,
                          &this_max_fd);
      if(this_max_fd > *max_fd)
        *max_fd = this_max_fd;
      break;

    case CURLM_STATE_DOING:
      Curl_doing_fdset(easy->easy_conn, read_fd_set, write_fd_set,
                       &this_max_fd);
      if(this_max_fd > *max_fd)
        *max_fd = this_max_fd;
      break;

    case CURLM_STATE_WAITCONNECT:
    case CURLM_STATE_DO_MORE:
      {
        /* when we're waiting for a connect, we wait for the socket to
           become writable */
        struct connectdata *conn = easy->easy_conn;
        curl_socket_t sockfd;

        if(CURLM_STATE_WAITCONNECT == easy->state) {
          sockfd = conn->sock[FIRSTSOCKET];
          FD_SET(sockfd, write_fd_set);
        }
        else {
          /* When in DO_MORE state, we could be either waiting for us
             to connect to a remote site, or we could wait for that site
             to connect to us. It makes a difference in the way: if we
             connect to the site we wait for the socket to become writable, if
             the site connects to us we wait for it to become readable */
          sockfd = conn->sock[SECONDARYSOCKET];
          FD_SET(sockfd, write_fd_set);
        }

        if((int)sockfd > *max_fd)
          *max_fd = (int)sockfd;
      }
      break;
    case CURLM_STATE_PERFORM:
      /* This should have a set of file descriptors for us to set.  */
      /* after the transfer is done, go DONE */

      Curl_single_fdset(easy->easy_conn,
                        read_fd_set, write_fd_set,
                        exc_fd_set, &this_max_fd);

      /* remember the maximum file descriptor */
      if(this_max_fd > *max_fd)
        *max_fd = this_max_fd;

      break;
    }
    easy = easy->next; /* check next handle */
  }

  return CURLM_OK;
}