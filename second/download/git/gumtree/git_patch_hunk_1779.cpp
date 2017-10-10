  */
 extern int parse_config_key(const char *var,
 			    const char *section,
 			    const char **subsection, int *subsection_len,
 			    const char **key);
 
+struct config_set_element {
+	struct hashmap_entry ent;
+	char *key;
+	struct string_list value_list;
+};
+
+struct configset_list_item {
+	struct config_set_element *e;
+	int value_index;
+};
+
+/*
+ * the contents of the list are ordered according to their
+ * position in the config files and order of parsing the files.
+ * (i.e. key-value pair at the last position of .git/config will
+ * be at the last item of the list)
+ */
+struct configset_list {
+	struct configset_list_item *items;
+	unsigned int nr, alloc;
+};
+
+struct config_set {
+	struct hashmap config_hash;
+	int hash_initialized;
+	struct configset_list list;
+};
+
+extern void git_configset_init(struct config_set *cs);
+extern int git_configset_add_file(struct config_set *cs, const char *filename);
+extern int git_configset_get_value(struct config_set *cs, const char *key, const char **value);
+extern const struct string_list *git_configset_get_value_multi(struct config_set *cs, const char *key);
+extern void git_configset_clear(struct config_set *cs);
+extern int git_configset_get_string_const(struct config_set *cs, const char *key, const char **dest);
+extern int git_configset_get_string(struct config_set *cs, const char *key, char **dest);
+extern int git_configset_get_int(struct config_set *cs, const char *key, int *dest);
+extern int git_configset_get_ulong(struct config_set *cs, const char *key, unsigned long *dest);
+extern int git_configset_get_bool(struct config_set *cs, const char *key, int *dest);
+extern int git_configset_get_bool_or_int(struct config_set *cs, const char *key, int *is_bool, int *dest);
+extern int git_configset_get_maybe_bool(struct config_set *cs, const char *key, int *dest);
+extern int git_configset_get_pathname(struct config_set *cs, const char *key, const char **dest);
+
+extern int git_config_get_value(const char *key, const char **value);
+extern const struct string_list *git_config_get_value_multi(const char *key);
+extern void git_config_clear(void);
+extern void git_config_iter(config_fn_t fn, void *data);
+extern int git_config_get_string_const(const char *key, const char **dest);
+extern int git_config_get_string(const char *key, char **dest);
+extern int git_config_get_int(const char *key, int *dest);
+extern int git_config_get_ulong(const char *key, unsigned long *dest);
+extern int git_config_get_bool(const char *key, int *dest);
+extern int git_config_get_bool_or_int(const char *key, int *is_bool, int *dest);
+extern int git_config_get_maybe_bool(const char *key, int *dest);
+extern int git_config_get_pathname(const char *key, const char **dest);
+
+struct key_value_info {
+	const char *filename;
+	int linenr;
+};
+
+extern NORETURN void git_die_config(const char *key, const char *err, ...) __attribute__((format(printf, 2, 3)));
+extern NORETURN void git_die_config_linenr(const char *key, const char *filename, int linenr);
+
 extern int committer_ident_sufficiently_given(void);
 extern int author_ident_sufficiently_given(void);
 
 extern const char *git_commit_encoding;
 extern const char *git_log_output_encoding;
 extern const char *git_mailmap_file;
 extern const char *git_mailmap_blob;
 
 /* IO helper functions */
 extern void maybe_flush_or_die(FILE *, const char *);
+__attribute__((format (printf, 2, 3)))
+extern void fprintf_or_die(FILE *, const char *fmt, ...);
 extern int copy_fd(int ifd, int ofd);
 extern int copy_file(const char *dst, const char *src, int mode);
 extern int copy_file_with_time(const char *dst, const char *src, int mode);
 extern void write_or_die(int fd, const void *buf, size_t count);
 extern int write_or_whine(int fd, const void *buf, size_t count, const char *msg);
 extern int write_or_whine_pipe(int fd, const void *buf, size_t count, const char *msg);
