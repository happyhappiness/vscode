f(canpipe) {
          /* We can pipeline if we want to. Let's continue looking for
             the optimal connection to use, i.e the shortest pipe that is not
             blacklisted. */

          if(pipeLen == 0) {
            /* We have the optimal connection. Let's stop looking. */
            chosen = check;
            break;
          }

          /* We can't use the connection if the pipe is full */
          if(max_pipe_len && (pipeLen >= max_pipe_len)) {
            infof(data, "Pipe is full, skip (%zu)\n", pipeLen);
            continue;
          }
#ifdef USE_NGHTTP2
          /* If multiplexed, make sure we don't go over concurrency limit */
          if(check->bits.multiplex) {
            /* Multiplexed connections can only be HTTP/2 for now */
            struct http_conn *httpc = &check->proto.httpc;
            if(pipeLen >= httpc->settings.max_concurrent_streams) {
              infof(data, "MAX_CONCURRENT_STREAMS reached, skip (%zu)\n",
                    pipeLen);
              continue;
            }
          }
#endif
          /* We can't use the connection if the pipe is penalized */
          if(Curl_pipeline_penalized(data, check)) {
            infof(data, "Penalized, skip\n");
            continue;
          }

          if(max_pipe_len) {
            if(pipeLen < best_pipe_len) {
              /* This connection has a shorter pipe so far. We'll pick this
                 and continue searching */
              chosen = check;
              best_pipe_len = pipeLen;
              continue;
            }
          }
          else {
            /* When not pipelining (== multiplexed), we have a match here! */
            chosen = check;
            infof(data, "Multiplexed connection found!\n");
            break;
          }
        }
        else {
          /* We have found a connection. Let's stop searching. */
          chosen = check;
          break;
        }