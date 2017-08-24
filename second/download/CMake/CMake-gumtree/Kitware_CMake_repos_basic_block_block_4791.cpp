f(data->easy_conn) {
          /* if this has a connection, unsubscribe from the pipelines */
          Curl_pipeline_leave_write(data->easy_conn);
          Curl_pipeline_leave_read(data->easy_conn);
          Curl_removeHandleFromPipeline(data, &data->easy_conn->send_pipe);
          Curl_removeHandleFromPipeline(data, &data->easy_conn->recv_pipe);

          if(stream_error) {
            /* Don't attempt to send data over a connection that timed out */
            bool dead_connection = result == CURLE_OPERATION_TIMEDOUT;
            /* disconnect properly */
            Curl_disconnect(data->easy_conn, dead_connection);

            /* This is where we make sure that the easy_conn pointer is reset.
               We don't have to do this in every case block above where a
               failure is detected */
            data->easy_conn = NULL;
          }
        }
        else if(data->mstate == CURLM_STATE_CONNECT) {
          /* Curl_connect() failed */
          (void)Curl_posttransfer(data);
        }