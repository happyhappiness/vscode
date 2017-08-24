{
      /* this socket has been removed. Tell the app to remove it */
      bool remove_sock_from_hash = TRUE;

      /* check if the socket to be removed serves a connection which has
         other easy-s in a pipeline. In this case the socket should not be
         removed. */
      struct connectdata *easy_conn = data->easy_conn;
      if(easy_conn) {
        if(easy_conn->recv_pipe.size > 1) {
          /* the handle should not be removed from the pipe yet */
          remove_sock_from_hash = FALSE;

          /* Update the sockhash entry to instead point to the next in line
             for the recv_pipe, or the first (in case this particular easy
             isn't already) */
          if(entry->easy == data) {
            if(Curl_recvpipe_head(data, easy_conn))
              entry->easy = easy_conn->recv_pipe.head->next->ptr;
            else
              entry->easy = easy_conn->recv_pipe.head->ptr;
          }
        }
        if(easy_conn->send_pipe.size > 1) {
          /* the handle should not be removed from the pipe yet */
          remove_sock_from_hash = FALSE;

          /* Update the sockhash entry to instead point to the next in line
             for the send_pipe, or the first (in case this particular easy
             isn't already) */
          if(entry->easy == data) {
            if(Curl_sendpipe_head(data, easy_conn))
              entry->easy = easy_conn->send_pipe.head->next->ptr;
            else
              entry->easy = easy_conn->send_pipe.head->ptr;
          }
        }
        /* Don't worry about overwriting recv_pipe head with send_pipe_head,
           when action will be asked on the socket (see multi_socket()), the
           head of the correct pipe will be taken according to the
           action. */
      }

      if(remove_sock_from_hash) {
        /* in this case 'entry' is always non-NULL */
        if(multi->socket_cb)
          multi->socket_cb(data,
                           s,
                           CURL_POLL_REMOVE,
                           multi->socket_userp,
                           entry->socketp);
        sh_delentry(&multi->sockhash, s);
      }
    }