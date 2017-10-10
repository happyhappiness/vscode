extern const char *git_mailmap_blob;

/* IO helper functions */
extern void maybe_flush_or_die(FILE *, const char *);
__attribute__((format (printf, 2, 3)))
extern void fprintf_or_die(FILE *, const char *fmt, ...);
extern int copy_fd(int ifd, int ofd);
extern int copy_file(const char *dst, const char *src, int mode);
extern int copy_file_with_time(const char *dst, const char *src, int mode);
extern void write_or_die(int fd, const void *buf, size_t count);
extern int write_or_whine(int fd, const void *buf, size_t count, const char *msg);
extern int write_or_whine_pipe(int fd, const void *buf, size_t count, const char *msg);
extern void fsync_or_die(int fd, const char *);

extern ssize_t read_in_full(int fd, void *buf, size_t count);
