static inline int readlink(const char *path, char *buf, size_t bufsiz)
{ errno = ENOSYS; return -1; }