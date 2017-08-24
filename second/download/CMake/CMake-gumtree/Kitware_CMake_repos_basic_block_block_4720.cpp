f(easy_owns_conn) {

      /* multi_done() clears the conn->data field to lose the association
         between the easy handle and the connection

         Note that this ignores the return code simply because there's
         nothing really useful to do with it anyway! */
      (void)multi_done(&data->easy_conn, data->result, premature);
    }
    else
      /* Clear connection pipelines, if multi_done above was not called */
      Curl_getoff_all_pipelines(data, data->easy_conn)