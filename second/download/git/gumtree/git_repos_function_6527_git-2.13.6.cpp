static inline pid_t getpgid(pid_t pid)
{ return pid == 0 ? getpid() : pid; }