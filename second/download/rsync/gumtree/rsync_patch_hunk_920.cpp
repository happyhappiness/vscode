 	lock.l_len = len;
 	lock.l_pid = 0;
 
 	return fcntl(fd,F_SETLK,&lock) == 0;
 }
 
-static int filter_server_path(char *arg)
-{
-	char *s;
+#define ENSURE_MEMSPACE(buf, type, sz, req) \
+	if ((req) > sz && !(buf = realloc_array(buf, type, sz = MAX(sz * 2, req)))) \
+		out_of_memory("glob_expand")
+
+static inline void call_glob_match(const char *name, int len, int from_glob,
+				   char *arg, int abpos, int fbpos);
+
+static struct glob_data {
+	char *arg_buf, *filt_buf, **argv;
+	int absize, fbsize, maxargs, argc;
+} glob;
+
+static void glob_match(char *arg, int abpos, int fbpos)
+{
+	int len;
+	char *slash;
+
+	while (*arg == '.' && arg[1] == '/') {
+		if (fbpos < 0) {
+			ENSURE_MEMSPACE(glob.filt_buf, char, glob.fbsize, glob.absize);
+			memcpy(glob.filt_buf, glob.arg_buf, abpos + 1);
+			fbpos = abpos;
+		}
+		ENSURE_MEMSPACE(glob.arg_buf, char, glob.absize, abpos + 3);
+		glob.arg_buf[abpos++] = *arg++;
+		glob.arg_buf[abpos++] = *arg++;
+		glob.arg_buf[abpos] = '\0';
+	}
+	if ((slash = strchr(arg, '/')) != NULL) {
+		*slash = '\0';
+		len = slash - arg;
+	} else
+		len = strlen(arg);
+	if (strpbrk(arg, "*?[")) {
+		struct dirent *di;
+		DIR *d;
+
+		if (!(d = opendir(abpos ? glob.arg_buf : ".")))
+			return;
+		while ((di = readdir(d)) != NULL) {
+			char *dname = d_name(di);
+			if (dname[0] == '.' && (dname[1] == '\0'
+			  || (dname[1] == '.' && dname[2] == '\0')))
+				continue;
+			if (!wildmatch(arg, dname))
+				continue;
+			call_glob_match(dname, strlen(dname), 1,
+					slash ? arg + len + 1 : NULL,
+					abpos, fbpos);
+		}
+		closedir(d);
+	} else {
+		call_glob_match(arg, len, 0,
+				slash ? arg + len + 1 : NULL,
+				abpos, fbpos);
+	}
+	if (slash)
+		*slash = '/';
+}
+
+static inline void call_glob_match(const char *name, int len, int from_glob,
+				   char *arg, int abpos, int fbpos)
+{
+	char *use_buf;
+
+	ENSURE_MEMSPACE(glob.arg_buf, char, glob.absize, abpos + len + 2);
+	memcpy(glob.arg_buf + abpos, name, len);
+	abpos += len;
+	glob.arg_buf[abpos] = '\0';
+
+	if (fbpos >= 0) {
+		ENSURE_MEMSPACE(glob.filt_buf, char, glob.fbsize, fbpos + len + 2);
+		memcpy(glob.filt_buf + fbpos, name, len);
+		fbpos += len;
+		glob.filt_buf[fbpos] = '\0';
+		use_buf = glob.filt_buf;
+	} else
+		use_buf = glob.arg_buf;
 
-	if (server_filter_list.head) {
-		for (s = arg; (s = strchr(s, '/')) != NULL; ) {
-			*s = '\0';
-			if (check_filter(&server_filter_list, arg, 1) < 0) {
-				/* We must leave arg truncated! */
-				return 1;
-			}
-			*s++ = '/';
+	if (from_glob || arg) {
+		STRUCT_STAT st;
+		int is_dir;
+
+		if (do_stat(glob.arg_buf, &st) != 0)
+			return;
+		is_dir = S_ISDIR(st.st_mode) != 0;
+		if (arg && !is_dir)
+			return;
+
+		if (daemon_filter_list.head
+		 && check_filter(&daemon_filter_list, FLOG, use_buf, is_dir) < 0)
+			return;
+	}
+
+	if (arg) {
+		glob.arg_buf[abpos++] = '/';
+		glob.arg_buf[abpos] = '\0';
+		if (fbpos >= 0) {
+			glob.filt_buf[fbpos++] = '/';
+			glob.filt_buf[fbpos] = '\0';
 		}
+		glob_match(arg, abpos, fbpos);
+	} else {
+		ENSURE_MEMSPACE(glob.argv, char *, glob.maxargs, glob.argc + 1);
+		if (!(glob.argv[glob.argc++] = strdup(glob.arg_buf)))
+			out_of_memory("glob_match");
 	}
-	return 0;
 }
 
-void glob_expand(char *s, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr)
+/* This routine performs wild-card expansion of the pathname in "arg".  Any
+ * daemon-excluded files/dirs will not be matched by the wildcards.  Returns 0
+ * if a wild-card string is the only returned item (due to matching nothing). */
+int glob_expand(const char *arg, char ***argv_p, int *argc_p, int *maxargs_p)
 {
-	char **argv = *argv_ptr;
-	int argc = *argc_ptr;
-	int maxargs = *maxargs_ptr;
-#if !defined HAVE_GLOB || !defined HAVE_GLOB_H
-	if (argc == maxargs) {
-		maxargs += MAX_ARGS;
-		if (!(argv = realloc_array(argv, char *, maxargs)))
-			out_of_memory("glob_expand");
-		*argv_ptr = argv;
-		*maxargs_ptr = maxargs;
-	}
-	if (!*s)
-		s = ".";
-	s = argv[argc++] = strdup(s);
-	filter_server_path(s);
-#else
-	glob_t globbuf;
+	int ret, save_argc;
+	char *s;
 
-	if (maxargs <= argc)
-		return;
-	if (!*s)
-		s = ".";
+	if (!arg) {
+		if (glob.filt_buf)
+			free(glob.filt_buf);
+		free(glob.arg_buf);
+		memset(&glob, 0, sizeof glob);
+		return -1;
+	}
 
 	if (sanitize_paths)
-		s = sanitize_path(NULL, s, "", 0);
-	else
-		s = strdup(s);
-	if (!s)
-		out_of_memory("glob_expand");
-
-	memset(&globbuf, 0, sizeof globbuf);
-	if (!filter_server_path(s))
-		glob(s, 0, NULL, &globbuf);
-	if (MAX((int)globbuf.gl_pathc, 1) > maxargs - argc) {
-		maxargs += globbuf.gl_pathc + MAX_ARGS;
-		if (!(argv = realloc_array(argv, char *, maxargs)))
+		s = sanitize_path(NULL, arg, "", 0, SP_KEEP_DOT_DIRS);
+	else {
+		s = strdup(arg);
+		if (!s)
 			out_of_memory("glob_expand");
-		*argv_ptr = argv;
-		*maxargs_ptr = maxargs;
+		clean_fname(s, CFN_KEEP_DOT_DIRS
+			     | CFN_KEEP_TRAILING_SLASH
+			     | CFN_COLLAPSE_DOT_DOT_DIRS);
 	}
-	if (globbuf.gl_pathc == 0)
-		argv[argc++] = s;
-	else {
-		int i;
+
+	ENSURE_MEMSPACE(glob.arg_buf, char, glob.absize, MAXPATHLEN);
+	*glob.arg_buf = '\0';
+
+	glob.argc = save_argc = *argc_p;
+	glob.argv = *argv_p;
+	glob.maxargs = *maxargs_p;
+
+	ENSURE_MEMSPACE(glob.argv, char *, glob.maxargs, 100);
+
+	glob_match(s, 0, -1);
+
+	/* The arg didn't match anything, so add the failed arg to the list. */
+	if (glob.argc == save_argc) {
+		ENSURE_MEMSPACE(glob.argv, char *, glob.maxargs, glob.argc + 1);
+		glob.argv[glob.argc++] = s;
+		ret = 0;
+	} else {
 		free(s);
-		for (i = 0; i < (int)globbuf.gl_pathc; i++) {
-			if (!(argv[argc++] = strdup(globbuf.gl_pathv[i])))
-				out_of_memory("glob_expand");
-		}
+		ret = 1;
 	}
-	globfree(&globbuf);
-#endif
-	*argc_ptr = argc;
+
+	*maxargs_p = glob.maxargs;
+	*argv_p = glob.argv;
+	*argc_p = glob.argc;
+
+	return ret;
 }
 
 /* This routine is only used in daemon mode. */
-void glob_expand_module(char *base1, char *arg, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr)
+void glob_expand_module(char *base1, char *arg, char ***argv_p, int *argc_p, int *maxargs_p)
 {
 	char *p, *s;
 	char *base = base1;
 	int base_len = strlen(base);
 
 	if (!arg || !*arg)
