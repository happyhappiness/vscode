(socketpair(AF_UNIX, SOCK_STREAM, 0, fds))
    return -errno;