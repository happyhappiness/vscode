void MmappedFile::doClose()
{
    if (fd >= 0) {
        file_close(fd);
        fd = -1;
        --store_open_disk_fd;
    }
}