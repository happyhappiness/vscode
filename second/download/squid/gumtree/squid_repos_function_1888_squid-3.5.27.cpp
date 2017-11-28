void
fd_bytes(int fd, int len, unsigned int type)
{
    fde *F = &fd_table[fd];

    if (len < 0)
        return;

    assert(type == FD_READ || type == FD_WRITE);

    if (type == FD_READ)
        F->bytes_read += len;
    else
        F->bytes_written += len;
}