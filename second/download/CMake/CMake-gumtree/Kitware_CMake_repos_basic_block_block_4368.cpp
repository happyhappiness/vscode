f(data->set.verbose)
          Curl_debug(data, CURLINFO_HEADER_IN,
                     line_start, (size_t)perline, conn)