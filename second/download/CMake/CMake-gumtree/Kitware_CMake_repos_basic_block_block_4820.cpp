f(data->set.max_recv_speed > 0)
          recv_timeout_ms = Curl_pgrsLimitWaitTime(data->progress.downloaded,
                                data->progress.dl_limit_size,
                                data->set.max_recv_speed,
                                data->progress.dl_limit_start,
                                now)