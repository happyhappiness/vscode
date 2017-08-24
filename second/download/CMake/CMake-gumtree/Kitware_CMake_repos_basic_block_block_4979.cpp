{
      failf(data,
            "CURLOPT_CONV_FROM_UTF8_FUNCTION callback returned %d: %s",
            (int)result, curl_easy_strerror(result));
    }