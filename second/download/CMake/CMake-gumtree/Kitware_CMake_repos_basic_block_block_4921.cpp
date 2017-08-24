f((ev_bitmask & CURL_POLL_OUT) &&
           data->easy_conn->send_pipe.head)
          data = data->easy_conn->send_pipe.head->ptr;
        else if((ev_bitmask & CURL_POLL_IN) &&
                data->easy_conn->recv_pipe.head)
          data = data->easy_conn->recv_pipe.head->ptr