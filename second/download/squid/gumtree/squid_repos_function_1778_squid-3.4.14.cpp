int
socket_write_method(int fd, const char *buf, int len)
{
    int i;
    PROF_start(send);
    i = send(fd, (const void *) buf, len, 0);
    PROF_stop(send);
    return i;
}