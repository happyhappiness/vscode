void
unlinkdUnlink(const char *path)
{
    char buf[MAXPATHLEN];
    int l;
    int bytes_written;
    static int queuelen = 0;

    if (unlinkd_wfd < 0) {
        debug_trap("unlinkdUnlink: unlinkd_wfd < 0");
        safeunlink(path, 0);
        return;
    }

    /*
     * If the queue length is greater than our limit, then we pause
     * for a small amount of time, hoping that unlinkd has some
     * feedback for us.  Maybe it just needs a slice of the CPU's
     * time.
     */
    if (queuelen >= UNLINKD_QUEUE_LIMIT) {
#if defined(USE_EPOLL) || defined(USE_KQUEUE) || defined(USE_DEVPOLL)
        /*
         * DPW 2007-04-23
         * We can't use fd_set when using epoll() or kqueue().  In
         * these cases we block for 10 ms.
         */
        xusleep(10000);
#else
        /*
         * DPW 2007-04-23
         * When we can use select, block for up to 100 ms.
         */
        struct timeval to;
        fd_set R;
        FD_ZERO(&R);
        FD_SET(unlinkd_rfd, &R);
        to.tv_sec = 0;
        to.tv_usec = 100000;
        select(unlinkd_rfd + 1, &R, NULL, NULL, &to);
#endif
    }

    /*
    * If there is at least one outstanding unlink request, then
    * try to read a response.  If there's nothing to read we'll
    * get an EWOULDBLOCK or whatever.  If we get a response, then
    * decrement the queue size by the number of newlines read.
    */
    if (queuelen > 0) {
        int bytes_read;
        int i;
        char rbuf[512];
        bytes_read = read(unlinkd_rfd, rbuf, 511);

        if (bytes_read > 0) {
            rbuf[bytes_read] = '\0';

            for (i = 0; i < bytes_read; i++)
                if ('\n' == rbuf[i])
                    queuelen--;

            assert(queuelen >= 0);
        }
    }

    l = strlen(path);
    assert(l < MAXPATHLEN);
    xstrncpy(buf, path, MAXPATHLEN);
    buf[l++] = '\n';
    bytes_written = write(unlinkd_wfd, buf, l);

    if (bytes_written < 0) {
        debugs(2, 1, "unlinkdUnlink: write FD " << unlinkd_wfd << " failed: " << xstrerror());
        safeunlink(path, 0);
        return;
    } else if (bytes_written != l) {
        debugs(2, 1, "unlinkdUnlink: FD " << unlinkd_wfd << " only wrote " << bytes_written << " of " << l << " bytes");
        safeunlink(path, 0);
        return;
    }

    statCounter.unlink.requests++;
    /*
    * Increment this syscalls counter here, even though the syscall
    * is executed by the helper process.  We try to be consistent
    * in counting unlink operations.
    */
    statCounter.syscalls.disk.unlinks++;
    queuelen++;
}