inline void SetHost(const char *src) {
        host_addr.SetEmpty();
        host_addr = src;
        if ( host_addr.IsAnyAddr() ) {
            xstrncpy(host, src, SQUIDHOSTNAMELEN);
            host_is_numeric = 0;
        } else {
            host_addr.ToHostname(host, SQUIDHOSTNAMELEN);
            debugs(23, 3, "HttpRequest::SetHost() given IP: " << host_addr);
            host_is_numeric = 1;
        }
    }