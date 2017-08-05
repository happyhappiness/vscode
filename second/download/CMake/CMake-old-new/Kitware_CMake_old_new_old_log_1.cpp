snprintf(buf, CURL_BUFSIZE(conn->data->set.buffer_size),
                 "%04d%02d%02d %02d:%02d:%02d GMT",
                 year, month, day, hour, minute, second);