FileOpeningConfig
FileOpeningConfig::ReadOnly()
{
    FileOpeningConfig cfg;

    /* I/O */
#if _SQUID_WINDOWS_
    cfg.desiredAccess = GENERIC_READ;
    cfg.shareMode = FILE_SHARE_READ;
#else
    cfg.openFlags = O_RDONLY;
#endif

    /* locking (if enabled later) */
#if _SQUID_WINDOWS_
    cfg.lockFlags = 0; // no named constant for a shared lock
#elif _SQUID_SOLARIS_
    cfg.lockType = F_RDLCK;
#else
    cfg.flockMode = LOCK_SH | LOCK_NB;
#endif

    return cfg;
}