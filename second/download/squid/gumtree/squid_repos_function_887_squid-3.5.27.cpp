bool
isOpen(const int fd)
{
    return fd >= 0 && fd_table && fd_table[fd].flags.open != 0;
}