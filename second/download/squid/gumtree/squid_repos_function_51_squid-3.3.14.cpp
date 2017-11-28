static ssize_t
mywrite(int fd, void *buf, size_t len)
{
#if _SQUID_WINDOWS_
    return send(fd, buf, len, 0);
#else
    alarm(io_timeout);
    return write(fd, buf, len);
#endif
}