f(result) {
        /* failure detected */
        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, TRUE);
        stream_error = TRUE;
      }