inline void SetHost(const char *src) {
        host_addr.setEmpty();
        host_addr = src;
        if (host_addr.isAnyAddr()) {
            xstrncpy(host, src, SQUIDHOSTNAMELEN);
            host_is_numeric = 0;
        } else {
            host_addr.toHostStr(host, SQUIDHOSTNAMELEN);
            debugs(23, 3, "HttpRequest::SetHost() given IP: " << host_addr);
            host_is_numeric = 1;
        }
        safe_free(canonical); // force its re-build
    }