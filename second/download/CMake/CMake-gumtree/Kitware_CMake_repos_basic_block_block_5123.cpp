f(conn->data->set.verbose)
    Curl_debug(conn->data, CURLINFO_HEADER_OUT,
               s, (size_t)bytes_written, conn)