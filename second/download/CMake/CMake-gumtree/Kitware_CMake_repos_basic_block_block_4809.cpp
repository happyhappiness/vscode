{
        /* If CURLE_RECV_ERROR happens early enough, we assume it was a race
         * condition and the server closed the re-used connection exactly when
         * we wanted to use it, so figure out if that is indeed the case.
         */
        CURLcode ret = Curl_retry_request(data->easy_conn, &newurl);
        if(!ret)
          retry = (newurl)?TRUE:FALSE;

        if(retry) {
          /* if we are to retry, set the result to OK and consider the
             request as done */
          result = CURLE_OK;
          done = TRUE;
        }
      }