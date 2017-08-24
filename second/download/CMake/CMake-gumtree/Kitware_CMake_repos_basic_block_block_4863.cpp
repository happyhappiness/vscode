{
            failf(data, "Operation timed out after %ld milliseconds with %"
                  CURL_FORMAT_CURL_OFF_T " out of %"
                  CURL_FORMAT_CURL_OFF_T " bytes received",
                  Curl_tvdiff(now, data->progress.t_startsingle),
                  k->bytecount, k->size);
          }