 	return NULL;
 }
 
 static const char *setup_nongit(const char *cwd, int *nongit_ok)
 {
 	if (!nongit_ok)
-		die("Not a git repository (or any of the parent directories): %s", DEFAULT_GIT_DIR_ENVIRONMENT);
+		die(_("Not a git repository (or any of the parent directories): %s"), DEFAULT_GIT_DIR_ENVIRONMENT);
 	if (chdir(cwd))
-		die_errno("Cannot come back to cwd");
+		die_errno(_("Cannot come back to cwd"));
 	*nongit_ok = 1;
 	return NULL;
 }
 
 static dev_t get_device_or_die(const char *path, const char *prefix, int prefix_len)
 {
