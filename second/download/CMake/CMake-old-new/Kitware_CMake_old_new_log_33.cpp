snprintf(buf, sizeof(data->state.buffer),
             "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size)