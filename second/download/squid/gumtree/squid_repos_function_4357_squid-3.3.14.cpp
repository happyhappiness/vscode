void Ssl::Lock::lock()
{

#if _SQUID_WINDOWS_
    hFile = CreateFile(TEXT(filename.c_str()), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
#else
    fd = open(filename.c_str(), 0);
    if (fd == -1)
#endif
        throw std::runtime_error("Failed to open file " + filename);

#if _SQUID_WINDOWS_
    if (!LockFile(hFile, 0, 0, 1, 0))
#else
    if (flock(fd, LOCK_EX) != 0)
#endif
        throw std::runtime_error("Failed to get a lock of " + filename);
}