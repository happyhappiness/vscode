f(easy_conn->send_pipe.size > 1) {
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