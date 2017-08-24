f(result) {
        /*
         * If an error was returned, and we aren't in completed state now,
         * then we go to completed and consider this transfer aborted.
         */

        /* NOTE: no attempt to disconnect connections must be made
           in the case blocks above - cleanup happens only here */

        data->state.pipe_broke = FALSE;

        /* Check if we can move pending requests to send pipe */
        Curl_multi_process_pending_handles(multi);

        if(data->easy_conn) {
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

        multistate(data, CURLM_STATE_COMPLETED);
      }
      /* if there's still a connection to use, call the progress function */
      else if(data->easy_conn && Curl_pgrsUpdate(data->easy_conn)) {
        /* aborted due to progress callback return code must close the
           connection */
        result = CURLE_ABORTED_BY_CALLBACK;
        streamclose(data->easy_conn, "Aborted by callback");

        /* if not yet in DONE state, go there, otherwise COMPLETED */
        multistate(data, (data->mstate < CURLM_STATE_DONE)?
                   CURLM_STATE_DONE: CURLM_STATE_COMPLETED);
        rc = CURLM_CALL_MULTI_PERFORM;
      }