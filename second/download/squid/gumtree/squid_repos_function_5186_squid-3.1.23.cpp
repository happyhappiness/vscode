void BlockingFile::doClose()
{
    if (fd > -1) {
        closed = true;
        file_close(fd);
        store_open_disk_fd--;
        fd = -1;
    }
}