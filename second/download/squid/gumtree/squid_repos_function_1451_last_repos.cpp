int
file_read_method(int fd, char *buf, int len)
{
    int i;
    PROF_start(read);
    i = _read(fd, buf, len);
    PROF_stop(read);
    return i;
}