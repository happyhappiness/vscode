 			*s++ = '/';
 		}
 	}
 	return 0;
 }
 
-static void glob_expand_one(char *s, char **argv, int *argc, int maxargs)
+static void glob_expand_one(char *s, char ***argv_ptr, int *argc_ptr,
+			    int *maxargs_ptr)
 {
+	char **argv = *argv_ptr;
+	int argc = *argc_ptr;
+	int maxargs = *maxargs_ptr;
 #if !(defined(HAVE_GLOB) && defined(HAVE_GLOB_H))
-	if (!*s) s = ".";
-	s = argv[*argc] = strdup(s);
+	if (argc == maxargs) {
+		maxargs += MAX_ARGS;
+		if (!(argv = realloc_array(argv, char *, maxargs)))
+			out_of_memory("glob_expand_one");
+		*argv_ptr = argv;
+		*maxargs_ptr = maxargs;
+	}
+	if (!*s)
+		s = ".";
+	s = argv[argc++] = strdup(s);
 	exclude_server_path(s);
-	(*argc)++;
 #else
-	extern int sanitize_paths;
 	glob_t globbuf;
 	int i;
 
-	if (!*s) s = ".";
+	if (maxargs <= argc)
+		return;
+	if (!*s)
+		s = ".";
 
-	s = argv[*argc] = strdup(s);
-	if (sanitize_paths) {
-		sanitize_path(s, NULL);
-	}
+	if (sanitize_paths)
+		s = sanitize_path(NULL, s, "", 0);
+	else
+		s = strdup(s);
 
 	memset(&globbuf, 0, sizeof globbuf);
 	if (!exclude_server_path(s))
 		glob(s, 0, NULL, &globbuf);
-	if (globbuf.gl_pathc == 0) {
-		(*argc)++;
-		globfree(&globbuf);
-		return;
+	if (MAX((int)globbuf.gl_pathc, 1) > maxargs - argc) {
+		maxargs += globbuf.gl_pathc + MAX_ARGS;
+		if (!(argv = realloc_array(argv, char *, maxargs)))
+			out_of_memory("glob_expand_one");
+		*argv_ptr = argv;
+		*maxargs_ptr = maxargs;
 	}
-	for (i = 0; i < maxargs - *argc && i < (int)globbuf.gl_pathc; i++) {
-		if (i == 0)
-			free(s);
-		argv[*argc + i] = strdup(globbuf.gl_pathv[i]);
-		if (!argv[*argc + i])
-			out_of_memory("glob_expand");
+	if (globbuf.gl_pathc == 0)
+		argv[argc++] = s;
+	else {
+		int j = globbuf.gl_pathc;
+		free(s);
+		for (i = 0; i < j; i++) {
+			if (!(argv[argc++] = strdup(globbuf.gl_pathv[i])))
+				out_of_memory("glob_expand_one");
+		}
 	}
 	globfree(&globbuf);
-	*argc += i;
 #endif
+	*argc_ptr = argc;
 }
 
 /* This routine is only used in daemon mode. */
-void glob_expand(char *base1, char **argv, int *argc, int maxargs)
+void glob_expand(char *base1, char ***argv_ptr, int *argc_ptr, int *maxargs_ptr)
 {
-	char *s = argv[*argc];
+	char *s = (*argv_ptr)[*argc_ptr];
 	char *p, *q;
 	char *base = base1;
 	int base_len = strlen(base);
 
-	if (!s || !*s) return;
+	if (!s || !*s)
+		return;
 
 	if (strncmp(s, base, base_len) == 0)
 		s += base_len;
 
-	s = strdup(s);
-	if (!s) out_of_memory("glob_expand");
+	if (!(s = strdup(s)))
+		out_of_memory("glob_expand");
 
-	if (asprintf(&base," %s/", base1) <= 0) out_of_memory("glob_expand");
+	if (asprintf(&base," %s/", base1) <= 0)
+		out_of_memory("glob_expand");
 	base_len++;
 
-	q = s;
-	while ((p = strstr(q,base)) != NULL && *argc < maxargs) {
-		/* split it at this point */
-		*p = 0;
-		glob_expand_one(q, argv, argc, maxargs);
-		q = p + base_len;
+	for (q = s; *q; q = p + base_len) {
+		if ((p = strstr(q, base)) != NULL)
+			*p = '\0'; /* split it at this point */
+		glob_expand_one(q, argv_ptr, argc_ptr, maxargs_ptr);
+		if (!p)
+			break;
 	}
 
-	if (*q && *argc < maxargs)
-		glob_expand_one(q, argv, argc, maxargs);
-
 	free(s);
 	free(base);
 }
 
 /**
  * Convert a string to lower case
  **/
 void strlower(char *s)
 {
 	while (*s) {
-		if (isupper(* (unsigned char *) s))
-			*s = tolower(* (unsigned char *) s);
+		if (isupper(*(unsigned char *)s))
+			*s = tolower(*(unsigned char *)s);
 		s++;
 	}
 }
 
 /* Join strings p1 & p2 into "dest" with a guaranteed '/' between them.  (If
  * p1 ends with a '/', no extra '/' is inserted.)  Returns the length of both
