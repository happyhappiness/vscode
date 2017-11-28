static void
fdUpdateBiggest(int fd, int opening)
{
    if (fd < Biggest_FD)
        return;

    assert(fd < Squid_MaxFD);

    if (fd > Biggest_FD) {
        /*
         * assert that we are not closing a FD bigger than
         * our known biggest FD
         */
        assert(opening);
        Biggest_FD = fd;
        return;
    }

    /* if we are here, then fd == Biggest_FD */
    /*
     * assert that we are closing the biggest FD; we can't be
     * re-opening it
     */
    assert(!opening);

    while (Biggest_FD >= 0 && !fd_table[Biggest_FD].flags.open)
        --Biggest_FD;
}