static void
comm_accept_try(int fd, void *)
{
    assert(isOpen(fd));
    fdc_table[fd].acceptNext();
}