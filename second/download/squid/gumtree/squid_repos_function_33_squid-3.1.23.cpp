static ssize_t
myread(int fd, void *buf, size_t len)
{
#ifndef _SQUID_MSWIN_
    alarm(io_timeout);
    return read(fd, buf, len);
#else

    return recv(fd, buf, len, 0);
#endif
}