static int
diskWriteIsComplete(int fd)
{
    return fd_table[fd].disk.write_q ? 0 : 1;
}