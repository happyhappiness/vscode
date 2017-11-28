static bool
DiskerOpen(const String &path, int flags, mode_t mode)
{
    assert(TheFile < 0);

    TheFile = file_open(path.termedBuf(), flags);

    if (TheFile < 0) {
        const int xerrno = errno;
        debugs(47, DBG_CRITICAL, HERE << "rock db error opening " << path << ": " <<
               xstrerr(xerrno));
        return false;
    }

    ++store_open_disk_fd;
    debugs(79,3, HERE << "rock db opened " << path << ": FD " << TheFile);
    return true;
}