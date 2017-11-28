void
File::close()
{
    if (!isOpen())
        return;
#if _SQUID_WINDOWS_
    if (!CloseHandle(fd_)) {
        const auto savedError = GetLastError();
        debugs(54, DBG_IMPORTANT, sysCallFailure("CloseHandle", WindowsErrorMessage(savedError)));
    }
#else
    if (::close(fd_) != 0) {
        const auto savedErrno = errno;
        debugs(54, DBG_IMPORTANT, sysCallError("close", savedErrno));
    }
#endif
    // closing the file handler implicitly removes all associated locks
}