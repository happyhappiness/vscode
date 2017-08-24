failf(data, "Connection timed out after %ld milliseconds",
                Curl_tvdiff(now, data->progress.t_startsingle))