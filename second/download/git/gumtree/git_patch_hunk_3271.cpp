 
 static char *resolve_relative_path(const char *rel)
 {
 	if (!starts_with(rel, "./") && !starts_with(rel, "../"))
 		return NULL;
 
-	if (!startup_info)
-		die("BUG: startup_info struct is not initialized.");
-
 	if (!is_inside_work_tree())
 		die("relative path syntax can't be used outside working tree.");
 
 	/* die() inside prefix_path() if resolved path is outside worktree */
 	return prefix_path(startup_info->prefix,
 			   startup_info->prefix ? strlen(startup_info->prefix) : 0,
