aprintf("Content-Range: bytes %s%" CURL_FORMAT_CURL_OFF_T
                  "/%" CURL_FORMAT_CURL_OFF_T "\r\n",
                  data->state.range, total_expected_size-1,
                  total_expected_size)