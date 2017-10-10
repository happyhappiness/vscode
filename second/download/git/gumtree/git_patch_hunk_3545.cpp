 	if (!path) {
 		logerror("'%s' does not appear to be a git repository", dir);
 		return NULL;
 	}
 
 	if ( ok_paths && *ok_paths ) {
-		char **pp;
+		const char **pp;
 		int pathlen = strlen(path);
 
 		/* The validation is done on the paths after enter_repo
 		 * appends optional {.git,.git/.git} and friends, but
 		 * it does not use getcwd().  So if your /pub is
 		 * a symlink to /mnt/pub, you can whitelist /pub and
