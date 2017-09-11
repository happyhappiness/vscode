    return -1;
}

int anetFormatIP(char *fmt, size_t fmt_len, char *ip, int port) {
    if (port >= 0)
        return snprintf(fmt,fmt_len,
            strchr(ip,':') ? "[%s]:%d" : "%s:%d", ip, port);
    else
        return snprintf(fmt, fmt_len, strchr(ip,':') ? "[%s]" : "%s", ip);
}

int anetFormatPeer(int fd, char *fmt, size_t fmt_len) {
    char ip[INET6_ADDRSTRLEN];
    int port;

    anetPeerToString(fd,ip,sizeof(ip),&port);
    return anetFormatIP(fmt, fmt_len, ip, port);
}

int anetSockName(int fd, char *ip, size_t ip_len, int *port) {
