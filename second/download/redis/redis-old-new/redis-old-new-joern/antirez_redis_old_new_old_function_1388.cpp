int anetFormatIP(char *fmt, size_t fmt_len, char *ip, int port) {
    if (port >= 0)
        return snprintf(fmt,fmt_len,
            strchr(ip,':') ? "[%s]:%d" : "%s:%d", ip, port);
    else
        return snprintf(fmt, fmt_len, strchr(ip,':') ? "[%s]" : "%s", ip);
}