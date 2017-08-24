f(Curl_recvpipe_head(data, easy_conn))
              entry->easy = easy_conn->recv_pipe.head->next->ptr;
            else
              entry->easy = easy_conn->recv_pipe.head->ptr