ap_log_rerror(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r,
                  conn->proxy_ips 
                      ? "Using %s as client's IP by proxies %s"
                      : "Using %s as client's IP by internal proxies",
                  conn->proxied_ip, conn->proxy_ips);