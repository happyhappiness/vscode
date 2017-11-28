void
commResetSelect(int fd)
{
    commSetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
    commSetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
}