
/*
 * Limit size of IO chunks, because huge chunks only cause pain.  OS X
 * 64-bit is buggy, returning EINVAL if len >= INT_MAX; and even in
 * the absence of bugs, large chunks can result in bad latencies when
 * you decide to kill the process.
 */
#define MAX_IO_SIZE (8*1024*1024)

/*
 * xread() is the same a read(), but it automatically restarts read()
 * operations with a recoverable error (EAGAIN and EINTR). xread()
 * DOES NOT GUARANTEE that "len" bytes is read even if the data is available.
 */
