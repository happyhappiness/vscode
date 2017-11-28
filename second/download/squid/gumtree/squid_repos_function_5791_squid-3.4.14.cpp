static void
DiskerClose(const String &path)
{
    if (TheFile >= 0) {
        file_close(TheFile);
        debugs(79,3, HERE << "rock db closed " << path << ": FD " << TheFile);
        TheFile = -1;
        --store_open_disk_fd;
    }
}