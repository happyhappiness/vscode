int
msghdr_write_method(int fd, const char *buf, int len)
{
    PROF_start(write);
    const int i = sendmsg(fd, reinterpret_cast<const msghdr*>(buf), MSG_NOSIGNAL);
    PROF_stop(write);
    return i > 0 ? len : i; // len is imprecise but the caller expects a match
}