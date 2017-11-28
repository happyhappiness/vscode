static ssize_t
mywrite(int fd, void *buf, size_t len)
{
#ifndef _SQUID_MSWIN_
    alarm(io_timeout);
    return write(fd, buf, len);
#else

    return send(fd, buf, len, 0);
#endif
}