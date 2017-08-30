snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),
             "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);