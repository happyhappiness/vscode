void
File::lockOnce(const FileOpeningConfig &cfg)
{
#if _SQUID_WINDOWS_
    if (!LockFileEx(fd_, cfg.lockFlags, 0, 0, 1, 0)) {
        const auto savedError = GetLastError();
        throw TexcHere(sysCallFailure("LockFileEx", WindowsErrorMessage(savedError).c_str()));
    }
#elif _SQUID_SOLARIS_
    if (fcntlLock(fd_, cfg.lockType) != 0) {
        const auto savedErrno = errno;
        throw TexcHere(sysCallError("fcntl(flock)", savedErrno));
    }
#else
    if (::flock(fd_, cfg.flockMode) != 0) {
        const auto savedErrno = errno;
        throw TexcHere(sysCallError("flock", savedErrno));
    }
#endif
    debugs(54, 3, "succeeded for " << name_);
}