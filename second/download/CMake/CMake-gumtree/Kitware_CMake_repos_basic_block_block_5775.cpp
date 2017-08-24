f(data->set.timeout) {
      now = Curl_tvnow();
      if(Curl_tvdiff(now, conn->created) >= data->set.timeout) {
        failf(data, "Time-out");
        result = CURLE_OPERATION_TIMEDOUT;
        keepon = FALSE;
      }
    }