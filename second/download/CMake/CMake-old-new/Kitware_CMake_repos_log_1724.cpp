aprintf("Content-Range: bytes %s/%" CURL_FORMAT_CURL_OFF_T "\r\n",
                  data->state.range, data->state.infilesize)