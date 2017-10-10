 		die("option %s needs an argument (check|on-demand)",
 				opt->long_name);
 
 	return 0;
 }
 
+static int git_push_config(const char *k, const char *v, void *cb)
+{
+	struct wt_status *s = cb;
+	int status;
+
+	status = git_gpg_config(k, v, NULL);
+	if (status)
+		return status;
+	return git_default_config(k, v, s);
+}
+
 int cmd_push(int argc, const char **argv, const char *prefix)
 {
 	int flags = 0;
 	int tags = 0;
 	int rc;
 	const char *repo = NULL;	/* default repository */
