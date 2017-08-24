{
        /* failure detected */
        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, FALSE);
        stream_error = TRUE;
      }