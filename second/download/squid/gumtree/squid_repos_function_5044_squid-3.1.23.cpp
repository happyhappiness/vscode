void DiskThreadsDiskFile::doClose()
{
    if (fd > -1) {
        statCounter.syscalls.disk.closes++;
#if ASYNC_CLOSE

        aioClose(fd);
        fd_close(fd);
#else

        aioCancel(fd);
        file_close(fd);
#endif

        store_open_disk_fd--;
        fd = -1;
    }
}