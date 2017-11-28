void
file_close(int fd)
{
    fde *F = &fd_table[fd];
    PF *read_callback;
    PROF_start(file_close);
    assert(fd >= 0);
    assert(F->flags.open);

    if ((read_callback = F->read_handler)) {
        F->read_handler = NULL;
        read_callback(-1, F->read_data);
    }

    if (F->flags.write_daemon) {
#if _SQUID_WINDOWS_ || _SQUID_OS2_
        /*
         * on some operating systems, you can not delete or rename
         * open files, so we won't allow delayed close.
         */
        while (!diskWriteIsComplete(fd))
            diskHandleWrite(fd, NULL);
#else
        F->flags.close_request = true;
        debugs(6, 2, "file_close: FD " << fd << ", delaying close");
        PROF_stop(file_close);
        return;
#endif

    }

    /*
     * Assert there is no write callback.  Otherwise we might be
     * leaking write state data by closing the descriptor
     */
    assert(F->write_handler == NULL);

#if CALL_FSYNC_BEFORE_CLOSE

    fsync(fd);

#endif

    close(fd);

    debugs(6, F->flags.close_request ? 2 : 5, "file_close: FD " << fd << " really closing\n");

    fd_close(fd);

    ++ statCounter.syscalls.disk.closes;

    PROF_stop(file_close);
}