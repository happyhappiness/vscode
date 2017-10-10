 	static const char *system_wide;
 	if (!system_wide)
 		system_wide = system_path(ETC_GITCONFIG);
 	return system_wide;
 }
 
+/*
+ * Parse environment variable 'k' as a boolean (in various
+ * possible spellings); if missing, use the default value 'def'.
+ */
 int git_env_bool(const char *k, int def)
 {
 	const char *v = getenv(k);
 	return v ? git_config_bool(k, v) : def;
 }
 
+/*
+ * Parse environment variable 'k' as ulong with possibly a unit
+ * suffix; if missing, use the default value 'val'.
+ */
+unsigned long git_env_ulong(const char *k, unsigned long val)
+{
+	const char *v = getenv(k);
+	if (v && !git_parse_ulong(v, &val))
+		die("failed to parse %s", k);
+	return val;
+}
+
 int git_config_system(void)
 {
 	return !git_env_bool("GIT_CONFIG_NOSYSTEM", 0);
 }
 
 int git_config_early(config_fn_t fn, void *data, const char *repo_config)
