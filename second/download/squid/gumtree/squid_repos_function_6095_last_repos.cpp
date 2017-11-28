void
File::open(const FileOpeningConfig &cfg)
{
#if _SQUID_WINDOWS_
    fd_ = CreateFile(TEXT(name_.c_str()), desiredAccess, shareMode, nullptr, creationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (fd_ == InvalidHandle) {
        const auto savedError = GetLastError();
        throw TexcHere(sysCallFailure("CreateFile", WindowsErrorMessage(savedError).c_str()));
    }
#else
    mode_t oldCreationMask = 0;
    const auto filename = name_.c_str(); // avoid complex operations inside enter_suid()
    enter_suid();
    if (cfg.creationMask)
        oldCreationMask = umask(cfg.creationMask); // XXX: Why here? Should not this be set for the whole Squid?
    fd_ = ::open(filename, cfg.openFlags, cfg.openMode);
    const auto savedErrno = errno;
    if (cfg.creationMask)
        umask(oldCreationMask);
    leave_suid();
    if (fd_ < 0)
        throw TexcHere(sysCallError("open", savedErrno));
#endif
}