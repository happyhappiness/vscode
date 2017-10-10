/*
 * Initializer for a "struct object_info" that wants no items. You may
 * also memset() the memory to all-zeroes.
 */
#define OBJECT_INFO_INIT {NULL}

/* Invoke lookup_replace_object() on the given hash */
#define OBJECT_INFO_LOOKUP_REPLACE 1
/* Allow reading from a loose object file of unknown/bogus type */
#define OBJECT_INFO_ALLOW_UNKNOWN_TYPE 2
/* Do not check cached storage */
#define OBJECT_INFO_SKIP_CACHED 4
/* Do not retry packed storage after checking packed and loose storage */
#define OBJECT_INFO_QUICK 8
extern int sha1_object_info_extended(const unsigned char *, struct object_info *, unsigned flags);
extern int packed_object_info(struct packed_git *pack, off_t offset, struct object_info *);

/* Dumb servers support */
extern int update_server_info(int);

extern const char *get_log_output_encoding(void);
extern const char *get_commit_output_encoding(void);

/*
 * This is a hack for test programs like test-dump-untracked-cache to
 * ensure that they do not modify the untracked cache when reading it.
 * Do not use it otherwise!
 */
extern int ignore_untracked_cache_config;

extern int committer_ident_sufficiently_given(void);
extern int author_ident_sufficiently_given(void);

extern const char *git_commit_encoding;
extern const char *git_log_output_encoding;
extern const char *git_mailmap_file;
