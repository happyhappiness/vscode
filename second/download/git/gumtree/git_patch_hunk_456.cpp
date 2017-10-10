 	while (serve_cache_loop(fd))
 		; /* nothing */
 
 	close(fd);
 }
 
-static const char permissions_advice[] =
+static const char permissions_advice[] = N_(
 "The permissions on your socket directory are too loose; other\n"
 "users may be able to read your cached credentials. Consider running:\n"
 "\n"
-"	chmod 0700 %s";
+"	chmod 0700 %s");
 static void init_socket_directory(const char *path)
 {
 	struct stat st;
 	char *path_copy = xstrdup(path);
 	char *dir = dirname(path_copy);
 
 	if (!stat(dir, &st)) {
 		if (st.st_mode & 077)
-			die(permissions_advice, dir);
+			die(_(permissions_advice), dir);
 	} else {
 		/*
 		 * We must be sure to create the directory with the correct mode,
 		 * not just chmod it after the fact; otherwise, there is a race
 		 * condition in which somebody can chdir to it, sleep, then try to open
 		 * our protected socket.
