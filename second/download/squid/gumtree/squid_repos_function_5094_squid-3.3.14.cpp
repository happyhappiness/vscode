void
Comm::ResetSelect(int fd)
{
    SetSelect(fd, COMM_SELECT_WRITE, NULL, NULL, 0);
    SetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
}