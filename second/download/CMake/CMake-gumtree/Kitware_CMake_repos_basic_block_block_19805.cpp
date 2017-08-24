(on && setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &delay, sizeof(delay)))
    return -errno;