static bool
DiskerOpen(const SBuf &path, int flags, mode_t mode)
{
    assert(TheFile < 0);

    DbName = path;
    TheFile = file_open(DbName.c_str(), flags);

    if (TheFile < 0) {
        const int xerrno = errno;
        debugs(47, DBG_CRITICAL, "ERROR: cannot open " << DbName << ": " <<
               xstrerr(xerrno));
        return false;
    }

    ++store_open_disk_fd;
    debugs(79,3, "rock db opened " << DbName << ": FD " << TheFile);
    return true;
}