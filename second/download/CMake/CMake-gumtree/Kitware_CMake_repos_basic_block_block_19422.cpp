(uv__pipe2(fds, flags | UV__O_CLOEXEC) == 0)
    return 0;