ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  req->proxy_ips
                      ? "Using %s as client's IP by proxies %s"
                      : "Using %s as client's IP by internal proxies%s",
                  req->useragent_ip,
                  (req->proxy_ips ? req->proxy_ips : ""));