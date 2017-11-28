FileOpeningConfig
FileOpeningConfig::ReadWrite()
{
    FileOpeningConfig cfg;

    /* I/O */
#if _SQUID_WINDOWS_
    cfg.desiredAccess = GENERIC_READ | GENERIC_WRITE;
    cfg.shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
#else
    cfg.openFlags = O_RDWR;
#endif

    /* locking (if enabled later) */
#if _SQUID_WINDOWS_
    cfg.lockFlags = LOCKFILE_EXCLUSIVE_LOCK;
#elif _SQUID_SOLARIS_
    cfg.lockType = F_WRLCK;
#else
    cfg.flockMode = LOCK_EX | LOCK_NB;
#endif

    return cfg;
}