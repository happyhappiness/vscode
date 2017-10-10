 */
extern int parse_config_key(const char *var,
			    const char *section,
			    const char **subsection, int *subsection_len,
			    const char **key);

extern int committer_ident_sufficiently_given(void);
extern int author_ident_sufficiently_given(void);

extern const char *git_commit_encoding;
extern const char *git_log_output_encoding;
extern const char *git_mailmap_file;
extern const char *git_mailmap_blob;

/* IO helper functions */
extern void maybe_flush_or_die(FILE *, const char *);
extern int copy_fd(int ifd, int ofd);
extern int copy_file(const char *dst, const char *src, int mode);
extern int copy_file_with_time(const char *dst, const char *src, int mode);
extern void write_or_die(int fd, const void *buf, size_t count);
extern int write_or_whine(int fd, const void *buf, size_t count, const char *msg);
extern int write_or_whine_pipe(int fd, const void *buf, size_t count, const char *msg);
