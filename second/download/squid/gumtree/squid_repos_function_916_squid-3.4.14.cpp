void
comm_init(void)
{
    fd_table =(fde *) xcalloc(Squid_MaxFD, sizeof(fde));
    fdd_table = (fd_debug_t *)xcalloc(Squid_MaxFD, sizeof(fd_debug_t));

    /* make sure the accept() socket FIFO delay queue exists */
    Comm::AcceptLimiter::Instance();

    // make sure the IO pending callback table exists
    Comm::CallbackTableInit();

    /* XXX account fd_table */
    /* Keep a few file descriptors free so that we don't run out of FD's
     * after accepting a client but before it opens a socket or a file.
     * Since Squid_MaxFD can be as high as several thousand, don't waste them */
    RESERVED_FD = min(100, Squid_MaxFD / 4);

    TheHalfClosed = new DescriptorSet;

    /* setup the select loop module */
    Comm::SelectLoopInit();
}