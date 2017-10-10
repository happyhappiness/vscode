#  define MAX_IO_SIZE SSIZE_MAX
# else
#  define MAX_IO_SIZE MAX_IO_SIZE_DEFAULT
# endif
#endif

/*
 * xread() is the same a read(), but it automatically restarts read()
 * operations with a recoverable error (EAGAIN and EINTR). xread()
 * DOES NOT GUARANTEE that "len" bytes is read even if the data is available.
 */
ssize_t xread(int fd, void *buf, size_t len)
