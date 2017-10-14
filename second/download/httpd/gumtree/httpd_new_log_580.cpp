ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "Digest: "
                              "applying AuthDigestEnableQueryStringHack "
                              "to uri <%s>", resp->raw_request_uri);