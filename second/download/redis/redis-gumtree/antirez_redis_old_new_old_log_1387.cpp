snprintf(fmt,fmt_len,
            strchr(ip,':') ? "[%s]:%d" : "%s:%d", ip, port);