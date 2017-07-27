aprintf("Content-Range: bytes 0-%" CURL_FORMAT_CURL_OFF_T
                  "/%" CURL_FORMAT_CURL_OFF_T "\r\n",
                  data->state.infilesize - 1, data->state.infilesize)