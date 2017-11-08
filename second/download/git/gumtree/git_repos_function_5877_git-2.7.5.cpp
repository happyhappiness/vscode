static inline int fsync(int fd)
{ return _commit(fd); }