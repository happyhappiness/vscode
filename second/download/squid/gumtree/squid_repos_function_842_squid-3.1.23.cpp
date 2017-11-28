static bool
isOpen(const int fd)
{
    return fd_table[fd].flags.open != 0;
}