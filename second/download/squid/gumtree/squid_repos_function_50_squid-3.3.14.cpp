static ssize_t
myread(int fd, void *buf, size_t len)
{
#if _SQUID_WINDOWS_
    return recv(fd, buf, len, 0);
#else
    alarm(io_timeout);
    return read(fd, buf, len);
#endif
}