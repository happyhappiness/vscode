{
      failf(data,
            "CURLOPT_CONV_TO_NETWORK_FUNCTION callback returned %d: %s",
            (int)result, curl_easy_strerror(result));
    }