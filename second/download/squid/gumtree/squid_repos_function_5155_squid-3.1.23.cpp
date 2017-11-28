bool
DiskdIOStrategy::optionQ1Parse(const char *name, const char *value, int isaReconfig)
{
    if (strcmp(name, "Q1") != 0)
        return false;

    int old_magic1 = magic1;

    magic1 = atoi(value);

    if (!isaReconfig)
        return true;

    if (old_magic1 < magic1) {
        /*
        * This is because shm.nbufs is computed at startup, when
        * we call shmget().  We can't increase the Q1/Q2 parameters
        * beyond their initial values because then we might have
        * more "Q2 messages" than shared memory chunks, and this
        * will cause an assertion in storeDiskdShmGet().
        */
        /* TODO: have DiskdIO hold a link to the swapdir, to allow detailed reporting again */
        debugs(3, 1, "WARNING: cannot increase cache_dir Q1 value while Squid is running.");
        magic1 = old_magic1;
        return true;
    }

    if (old_magic1 != magic1)
        debugs(3, 1, "cache_dir new Q1 value '" << magic1 << "'");

    return true;
}