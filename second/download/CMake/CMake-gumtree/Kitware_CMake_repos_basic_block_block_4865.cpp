f(data->mstate == CURLM_STATE_WAITCONNECT)
          failf(data, "Connection timed out after %ld milliseconds",
                Curl_tvdiff(now, data->progress.t_startsingle))