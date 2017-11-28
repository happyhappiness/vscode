bool Ssl::Lock::locked() const
{
#if _SQUID_WINDOWS_
    return hFile != INVALID_HANDLE_VALUE;
#else
    return fd != -1;
#endif
}