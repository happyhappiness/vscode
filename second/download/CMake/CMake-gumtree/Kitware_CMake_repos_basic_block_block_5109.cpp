{
    /* if timeout is requested, find out how much remaining time we have */
    timeout2_ms = data->set.timeout - /* timeout time */
      Curl_tvdiff(Curl_tvnow(), conn->now); /* spent time */

    /* pick the lowest number */
    timeout_ms = CURLMIN(timeout_ms, timeout2_ms);
  }