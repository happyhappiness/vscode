send_timeout_ms = Curl_pgrsLimitWaitTime(data->progress.uploaded,
                                data->progress.ul_limit_size,
                                data->set.max_send_speed,
                                data->progress.ul_limit_start,
                                now)