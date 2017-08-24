f(send_timeout_ms >= recv_timeout_ms)
          Curl_expire(data, send_timeout_ms, EXPIRE_TOOFAST);
        else
          Curl_expire(data, recv_timeout_ms, EXPIRE_TOOFAST)