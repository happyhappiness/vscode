  */
 extern int ignore_untracked_cache_config;
 
 struct key_value_info {
 	const char *filename;
 	int linenr;
+	enum config_origin_type origin_type;
+	enum config_scope scope;
 };
 
 extern NORETURN void git_die_config(const char *key, const char *err, ...) __attribute__((format(printf, 2, 3)));
 extern NORETURN void git_die_config_linenr(const char *key, const char *filename, int linenr);
 
 extern int committer_ident_sufficiently_given(void);
