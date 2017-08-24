f(entry->easy == data) {
            if(Curl_sendpipe_head(data, easy_conn))
              entry->easy = easy_conn->send_pipe.head->next->ptr;
            else
              entry->easy = easy_conn->send_pipe.head->ptr;
          }