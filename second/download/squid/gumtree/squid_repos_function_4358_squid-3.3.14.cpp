void Ssl::Lock::unlock()
{
#if _SQUID_WINDOWS_
    if (hFile != INVALID_HANDLE_VALUE) {
        UnlockFile(hFile, 0, 0, 1, 0);
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }
#else
    if (fd != -1) {
        flock(fd, LOCK_UN);
        close(fd);
        fd = -1;
    }
#endif
    else
        throw std::runtime_error("Lock is already unlocked for " + filename);
}