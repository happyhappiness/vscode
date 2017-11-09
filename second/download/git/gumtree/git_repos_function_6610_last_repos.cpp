static inline pid_t fork(void)
{ errno = ENOSYS; return -1; }