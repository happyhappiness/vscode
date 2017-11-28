int
comm_has_pending_read_callback(int fd)
{
    assert(isOpen(fd));
    // XXX: We do not know whether there is a read callback scheduled.
    // This is used for pconn management that should probably be more
    // tightly integrated into comm to minimize the chance that a
    // closing pconn socket will be used for a new transaction.
    return false;
}