FileOpeningConfig &
FileOpeningConfig::createdIfMissing()
{
#if _SQUID_WINDOWS_
    Must((desiredAccess & GENERIC_WRITE) == GENERIC_WRITE);
    creationDisposition = OPEN_ALWAYS;
#else
    Must((openFlags & O_RDWR) == O_RDWR);
    openFlags |= O_CREAT;
    creationMask = (S_IXUSR | S_IXGRP|S_IWGRP | S_IXOTH|S_IWOTH); // unwanted bits
#endif
    return *this;
}