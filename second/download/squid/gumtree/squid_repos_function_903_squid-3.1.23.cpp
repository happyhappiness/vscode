void
comm_init(void)
{
    fd_table =(fde *) xcalloc(Squid_MaxFD, sizeof(fde));
    fdd_table = (fd_debug_t *)xcalloc(Squid_MaxFD, sizeof(fd_debug_t));

    fdc_table = new AcceptFD[Squid_MaxFD];
    for (int pos = 0; pos < Squid_MaxFD; ++pos) {
        fdc_table[pos] = AcceptFD(pos);
    }

    commfd_table = (comm_fd_t *) xcalloc(Squid_MaxFD, sizeof(comm_fd_t));
    for (int pos = 0; pos < Squid_MaxFD; pos++) {
        commfd_table[pos].fd = pos;
        commfd_table[pos].readcb.fd = pos;
        commfd_table[pos].readcb.type = IOCB_READ;
        commfd_table[pos].writecb.fd = pos;
        commfd_table[pos].writecb.type = IOCB_WRITE;
    }

    /* XXX account fd_table */
    /* Keep a few file descriptors free so that we don't run out of FD's
     * after accepting a client but before it opens a socket or a file.
     * Since Squid_MaxFD can be as high as several thousand, don't waste them */
    RESERVED_FD = min(100, Squid_MaxFD / 4);

    conn_close_pool = memPoolCreate("close_handler", sizeof(close_handler));

    TheHalfClosed = new DescriptorSet;
}