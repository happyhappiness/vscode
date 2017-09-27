        }
    }

    r->useragent_addr = req->useragent_addr;
    r->useragent_ip = req->useragent_ip;

    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                  req->proxy_ips
                      ? "Using %s as client's IP by proxies %s"
                      : "Using %s as client's IP by internal proxies",
                  req->useragent_ip, req->proxy_ips);
    return OK;
}
