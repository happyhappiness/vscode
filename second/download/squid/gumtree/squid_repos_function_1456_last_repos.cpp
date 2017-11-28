int
msghdr_read_method(int fd, char *buf, int)
{
    PROF_start(read);
    const int i = recvmsg(fd, reinterpret_cast<msghdr*>(buf), MSG_DONTWAIT);
    PROF_stop(read);
    return i;
}