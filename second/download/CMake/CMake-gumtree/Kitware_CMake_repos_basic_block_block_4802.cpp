{
          /* after the transfer is done, go DONE */

          /* but first check to see if we got a location info even though we're
             not following redirects */
          if(data->req.location) {
            free(newurl);
            newurl = data->req.location;
            data->req.location = NULL;
            result = Curl_follow(data, newurl, FOLLOW_FAKE);
            if(result)
              stream_error = TRUE;
          }

          multistate(data, CURLM_STATE_DONE);
          rc = CURLM_CALL_MULTI_PERFORM;
        }