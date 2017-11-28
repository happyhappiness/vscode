int
file_write_method(int fd, const char *buf, int len)
{
    int i;
    PROF_start(write);
    i = (_write(fd, buf, len));
    PROF_stop(write);
    return i;
}