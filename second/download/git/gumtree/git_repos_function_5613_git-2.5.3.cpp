static inline int fchmod(int fildes, mode_t mode)
{ errno = ENOSYS; return -1; }