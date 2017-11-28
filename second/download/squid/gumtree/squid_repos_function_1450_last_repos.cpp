int
socket_read_method(int fd, char *buf, int len)
{
    int i;
    PROF_start(recv);
    i = recv(fd, (void *) buf, len, 0);
    PROF_stop(recv);
    return i;
}