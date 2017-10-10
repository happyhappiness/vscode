 
 	if (!path)
 		return config_error_nonbool("include.path");
 
 	expanded = expand_user_path(path);
 	if (!expanded)
-		return error("Could not expand include path '%s'", path);
+		return error("could not expand include path '%s'", path);
 	path = expanded;
 
 	/*
 	 * Use an absolute path as-is, but interpret relative paths
 	 * based on the including config file.
 	 */
