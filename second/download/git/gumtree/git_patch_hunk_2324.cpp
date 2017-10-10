 	if (pthread_join(async->tid, &ret))
 		error("pthread_join failed");
 	return (int)(intptr_t)ret;
 #endif
 }
 
-char *find_hook(const char *name)
+const char *find_hook(const char *name)
 {
-	char *path = git_path("hooks/%s", name);
+	const char *path = git_path("hooks/%s", name);
 	if (access(path, X_OK) < 0)
 		path = NULL;
 
 	return path;
 }
 
