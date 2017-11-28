void
File::truncate()
{
#if _SQUID_WINDOWS_
    if (!SetFilePointer(fd_, 0, nullptr, FILE_BEGIN)) {
        const auto savedError = GetLastError();
        throw TexcHere(sysCallFailure("SetFilePointer", WindowsErrorMessage(savedError).c_str()));
    }

    if (!SetEndOfFile(fd_)) {
        const auto savedError = GetLastError();
        throw TexcHere(sysCallFailure("SetEndOfFile", WindowsErrorMessage(savedError).c_str()));
    }
#else
    if (::lseek(fd_, SEEK_SET, 0) < 0) {
        const auto savedErrno = errno;
        throw TexcHere(sysCallError("lseek", savedErrno));
    }

    if (::ftruncate(fd_, 0) != 0) {
        const auto savedErrno = errno;
        throw TexcHere(sysCallError("ftruncate", savedErrno));
    }
#endif
}