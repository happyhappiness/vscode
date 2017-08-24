{
    /* use translation callback */
    CURLcode result = data->set.convfromnetwork(buffer, length);
    if(result) {
      failf(data,
            "CURLOPT_CONV_FROM_NETWORK_FUNCTION callback returned %d: %s",
            (int)result, curl_easy_strerror(result));
    }

    return result;
  }