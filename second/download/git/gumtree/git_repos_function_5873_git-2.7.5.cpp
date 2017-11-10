static inline int symlink(const char *oldpath, const char *newpath)
{ errno = ENOSYS; return -1; }