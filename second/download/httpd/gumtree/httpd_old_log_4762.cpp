ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "Encountered FakeBasicAuth spoof: %s", username);