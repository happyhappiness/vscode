 		*argv = new_argv;
 		*argcp += count - 1;
 
 		ret = 1;
 	}
 
-	if (subdir && chdir(subdir))
-		die_errno("Cannot change to '%s'", subdir);
+	restore_env(0);
 
 	errno = saved_errno;
 
 	return ret;
 }
 
