void
File::synchronize()
{
#if _SQUID_WINDOWS_
    if (!FlushFileBuffers(fd_)) {
        const auto savedError = GetLastError();
        throw TexcHere(sysCallFailure("FlushFileBuffers", WindowsErrorMessage(savedError).c_str()));
    }
#else
    if (::fsync(fd_) != 0) {
        const auto savedErrno = errno;
        throw TexcHere(sysCallError("fsync", savedErrno));
    }
#endif
}