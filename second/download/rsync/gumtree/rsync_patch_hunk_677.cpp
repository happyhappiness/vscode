 		ret->include = 1;
 		pattern += 2;
 	} else {
 		ret->include = include;
 	}
 
-	ret->pattern = strdup(pattern);
-
-	if (!ret->pattern) out_of_memory("make_exclude");
+	if (exclude_path_prefix)
+		ret->match_flags |= MATCHFLG_ABS_PATH;
+	if (exclude_path_prefix && *pattern == '/') {
+		ret->pattern = new_array(char,
+			strlen(exclude_path_prefix) + strlen(pattern) + 1);
+		if (!ret->pattern) out_of_memory("make_exclude");
+		sprintf(ret->pattern, "%s%s", exclude_path_prefix, pattern);
+	}
+	else {
+		ret->pattern = strdup(pattern);
+		if (!ret->pattern) out_of_memory("make_exclude");
+	}
 
 	if (strpbrk(pattern, "*[?")) {
-	    ret->regular_exp = 1;
-	    ret->fnmatch_flags = FNM_PATHNAME;
-	    if (strstr(pattern, "**")) {
-		    static int tested;
-		    if (!tested) {
-			    tested = 1;
-			    if (fnmatch("a/b/*", "a/b/c/d", FNM_PATHNAME)==0) {
-				    rprintf(FERROR,"WARNING: fnmatch FNM_PATHNAME is broken on your system\n");
-			    }
-		    }
-		    ret->fnmatch_flags = 0;
-	    }
+		ret->match_flags |= MATCHFLG_WILD;
+		if (strstr(pattern, "**")) {
+			ret->match_flags |= MATCHFLG_WILD2;
+			/* If the pattern starts with **, note that. */
+			if (*pattern == '*' && pattern[1] == '*')
+				ret->match_flags |= MATCHFLG_WILD2_PREFIX;
+		}
 	}
 
-	if (strlen(pattern) > 1 && pattern[strlen(pattern)-1] == '/') {
-		ret->pattern[strlen(pattern)-1] = 0;
+	pat_len = strlen(ret->pattern);
+	if (pat_len > 1 && ret->pattern[pat_len-1] == '/') {
+		ret->pattern[pat_len-1] = 0;
 		ret->directory = 1;
 	}
 
-	if (!strchr(ret->pattern,'/')) {
-		ret->local = 1;
-	}
+	for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
+		ret->slash_cnt++;
 
 	return ret;
 }
 
 static void free_exclude(struct exclude_struct *ex)
 {
 	free(ex->pattern);
 	memset(ex,0,sizeof(*ex));
 	free(ex);
 }
 
+
+void free_exclude_list(struct exclude_struct ***listp)
+{
+	struct exclude_struct **list = *listp;
+
+	if (verbose > 2)
+		rprintf(FINFO,"clearing exclude list\n");
+
+	if (!list)
+		return;
+
+	while (*list)
+		free_exclude(*list++);
+
+	free(*listp);
+	*listp = NULL;
+}
+
 static int check_one_exclude(char *name, struct exclude_struct *ex,
-                             STRUCT_STAT *st)
+                             int name_is_dir)
 {
 	char *p;
-	int match_start=0;
+	int match_start = 0;
 	char *pattern = ex->pattern;
 
-	if (ex->local && (p=strrchr(name,'/')))
-		name = p+1;
+	/* If the pattern does not have any slashes AND it does not have
+	 * a "**" (which could match a slash), then we just match the
+	 * name portion of the path. */
+	if (!ex->slash_cnt && !(ex->match_flags & MATCHFLG_WILD2)) {
+		if ((p = strrchr(name,'/')) != NULL)
+			name = p+1;
+	}
+	else if ((ex->match_flags & MATCHFLG_ABS_PATH) && *name != '/') {
+		static char full_name[MAXPATHLEN];
+		extern char curr_dir[];
+		int plus = curr_dir[1] == '\0'? 1 : 0;
+		snprintf(full_name, sizeof full_name,
+			 "%s/%s", curr_dir+plus, name);
+		name = full_name;
+	}
 
 	if (!name[0]) return 0;
 
-	if (ex->directory && !S_ISDIR(st->st_mode)) return 0;
+	if (ex->directory && !name_is_dir) return 0;
 
-	if (*pattern == '/' && *name != '/') {
+	if (*pattern == '/') {
 		match_start = 1;
 		pattern++;
+		if (*name == '/')
+			name++;
 	}
 
-	if (ex->regular_exp) {
-		if (fnmatch(pattern, name, ex->fnmatch_flags) == 0) {
+	if (ex->match_flags & MATCHFLG_WILD) {
+		/* A non-anchored match with an infix slash and no "**"
+		 * needs to match the last slash_cnt+1 name elements. */
+		if (!match_start && ex->slash_cnt &&
+		    !(ex->match_flags & MATCHFLG_WILD2)) {
+			int cnt = ex->slash_cnt + 1;
+			for (p = name + strlen(name) - 1; p >= name; p--) {
+				if (*p == '/' && !--cnt)
+					break;
+			}
+			name = p+1;
+		}
+		if (wildmatch(pattern, name))
 			return 1;
+		if (ex->match_flags & MATCHFLG_WILD2_PREFIX) {
+			/* If the **-prefixed pattern has a '/' as the next
+			 * character, then try to match the rest of the
+			 * pattern at the root. */
+			if (pattern[2] == '/' && wildmatch(pattern+3, name))
+				return 1;
+		}
+		else if (!match_start && ex->match_flags & MATCHFLG_WILD2) {
+			/* A non-anchored match with an infix or trailing "**"
+			 * (but not a prefixed "**") needs to try matching
+			 * after every slash. */
+			while ((name = strchr(name, '/')) != NULL) {
+				name++;
+				if (wildmatch(pattern, name))
+					return 1;
+			}
 		}
+	} else if (match_start) {
+		if (strcmp(name,pattern) == 0)
+			return 1;
 	} else {
 		int l1 = strlen(name);
 		int l2 = strlen(pattern);
-		if (l2 <= l1 && 
+		if (l2 <= l1 &&
 		    strcmp(name+(l1-l2),pattern) == 0 &&
-		    (l1==l2 || (!match_start && name[l1-(l2+1)] == '/'))) {
+		    (l1==l2 || name[l1-(l2+1)] == '/')) {
 			return 1;
 		}
 	}
 
 	return 0;
 }
 
 
 static void report_exclude_result(char const *name,
                                   struct exclude_struct const *ent,
-                                  STRUCT_STAT const *st)
+                                  int name_is_dir)
 {
         /* If a trailing slash is present to match only directories,
          * then it is stripped out by make_exclude.  So as a special
          * case we add it back in here. */
-        
+
         if (verbose >= 2)
                 rprintf(FINFO, "%s %s %s because of pattern %s%s\n",
                         ent->include ? "including" : "excluding",
-                        S_ISDIR(st->st_mode) ? "directory" : "file",
+			name_is_dir ? "directory" : "file",
                         name, ent->pattern,
                         ent->directory ? "/" : "");
 }
 
 
 /*
  * Return true if file NAME is defined to be excluded by either
  * LOCAL_EXCLUDE_LIST or the globals EXCLUDE_LIST.
  */
-int check_exclude(char *name, struct exclude_struct **local_exclude_list,
-		  STRUCT_STAT *st)
+int check_exclude(struct exclude_struct **list, char *name, int name_is_dir)
 {
-	int n;
         struct exclude_struct *ent;
 
-	if (name && (name[0] == '.') && !name[1])
-		/* never exclude '.', even if somebody does --exclude '*' */
-		return 0;
-
-	if (exclude_list) {
-		for (n=0; exclude_list[n]; n++) {
-                        ent = exclude_list[n];
-			if (check_one_exclude(name, ent, st)) {
-                                report_exclude_result(name, ent, st);
-				return !ent->include;
-                        }
-                }
-	}
-
-	if (local_exclude_list) {
-		for (n=0; local_exclude_list[n]; n++) {
-                        ent = local_exclude_list[n];
-			if (check_one_exclude(name, ent, st)) {
-                                report_exclude_result(name, ent, st);
-				return !ent->include;
-                        }
+	while ((ent = *list++) != NULL) {
+		if (check_one_exclude(name, ent, name_is_dir)) {
+			report_exclude_result(name, ent, name_is_dir);
+			return !ent->include;
                 }
 	}
 
 	return 0;
 }
 
 
-void add_exclude_list(const char *pattern, struct exclude_struct ***list, int include)
+void add_exclude(struct exclude_struct ***listp, const char *pattern, int include)
 {
-	int len=0;
-	if (list && *list)
-		for (; (*list)[len]; len++) ;
-
-	if (strcmp(pattern,"!") == 0) {
-		if (verbose > 2)
-			rprintf(FINFO,"clearing exclude list\n");
-		while ((len)--) {
-			free_exclude((*list)[len]);
-		}
-		free((*list));
-		*list = NULL;
-		return;
+	struct exclude_struct **list = *listp;
+	int len = 0;
+
+	if (*pattern == '!' && !pattern[1]) {
+	    free_exclude_list(listp);
+	    return;
 	}
 
-	*list = realloc_array(*list, struct exclude_struct *, len+2);
-	
-	if (!*list || !((*list)[len] = make_exclude(pattern, include)))
+	if (list)
+		for (; list[len]; len++) {}
+
+ 	list = *listp = realloc_array(list, struct exclude_struct *, len+2);
+
+	if (!list || !(list[len] = make_exclude(pattern, include)))
 		out_of_memory("add_exclude");
-	
+
 	if (verbose > 2) {
 		rprintf(FINFO,"add_exclude(%s,%s)\n",pattern,
-			      include ? "include" : "exclude");
+			include ? "include" : "exclude");
 	}
 
-	(*list)[len+1] = NULL;
+	list[len+1] = NULL;
 }
 
-void add_exclude(const char *pattern, int include)
-{
-	add_exclude_list(pattern,&exclude_list, include);
-}
 
-struct exclude_struct **make_exclude_list(const char *fname,
-					  struct exclude_struct **list1,
-					  int fatal, int include)
+void add_exclude_file(struct exclude_struct ***listp, const char *fname,
+		      int fatal, int include)
 {
-	struct exclude_struct **list=list1;
-	FILE *f;
+	int fd;
 	char line[MAXPATHLEN];
+	char *eob = line + MAXPATHLEN - 1;
+	extern int eol_nulls;
 
-	if (strcmp(fname, "-")) {
-		f = fopen(fname,"r");
-	} else {
-		f = fdopen(0, "r");
-	}
-	if (!f) {
+	if (!fname || !*fname)
+		return;
+
+	if (*fname != '-' || fname[1])
+		fd = open(fname, O_RDONLY|O_BINARY);
+	else
+		fd = 0;
+	if (fd < 0) {
 		if (fatal) {
 			rsyserr(FERROR, errno,
                                 "failed to open %s file %s",
                                 include ? "include" : "exclude",
                                 fname);
 			exit_cleanup(RERR_FILEIO);
 		}
-		return list;
+		return;
 	}
 
-	while (fgets(line,MAXPATHLEN,f)) {
-		int l = strlen(line);
-		while (l && (line[l-1] == '\n' || line[l-1] == '\r')) l--;
-		line[l] = 0;
-		if (line[0] && (line[0] != ';') && (line[0] != '#')) {
+	while (1) {
+		char ch, *s = line;
+		int cnt;
+		while (1) {
+			if ((cnt = read(fd, &ch, 1)) <= 0) {
+				if (cnt < 0 && errno == EINTR)
+					continue;
+				break;
+			}
+			if (eol_nulls? !ch : (ch == '\n' || ch == '\r'))
+				break;
+			if (s < eob)
+				*s++ = ch;
+		}
+		*s = '\0';
+		if (*line && *line != ';' && *line != '#') {
 			/* Skip lines starting with semicolon or pound.
-			   It probably wouldn't cause any harm to not skip
-			     them but there's no need to save them. */
-			add_exclude_list(line,&list,include);
+			 * It probably wouldn't cause any harm to not skip
+			 * them but there's no need to save them. */
+			add_exclude(listp, line, include);
 		}
+		if (cnt <= 0)
+			break;
 	}
-	fclose(f);
-	return list;
-}
-
-
-void add_exclude_file(const char *fname, int fatal, int include)
-{
-	if (!fname || !*fname) return;
-
-	exclude_list = make_exclude_list(fname,exclude_list,fatal,include);
+	close(fd);
 }
 
 
 void send_exclude_list(int f)
 {
 	int i;
-	extern int remote_version;
+	extern int protocol_version;
 	extern int list_only, recurse;
 
 	/* This is a complete hack - blame Rusty.
 	 *
 	 * FIXME: This pattern shows up in the output of
 	 * report_exclude_result(), which is not ideal. */
-	if (list_only && !recurse) {
-		add_exclude("/*/*", 0);
-	}
+	if (list_only && !recurse)
+		add_exclude(&exclude_list, "/*/*", ADD_EXCLUDE);
 
 	if (!exclude_list) {
 		write_int(f,0);
 		return;
 	}
 
 	for (i=0;exclude_list[i];i++) {
 		int l;
 		char pattern[MAXPATHLEN];
 
-		strlcpy(pattern,exclude_list[i]->pattern,sizeof(pattern)); 
+		strlcpy(pattern,exclude_list[i]->pattern,sizeof(pattern));
 		if (exclude_list[i]->directory) strlcat(pattern,"/", sizeof(pattern));
 
 		l = strlen(pattern);
 		if (l == 0) continue;
 		if (exclude_list[i]->include) {
-			if (remote_version < 19) {
+			if (protocol_version < 19) {
 				rprintf(FERROR,"remote rsync does not support include syntax - aborting\n");
 				exit_cleanup(RERR_UNSUPPORTED);
 			}
 			write_int(f,l+2);
 			write_buf(f,"+ ",2);
 		} else {
 			write_int(f,l);
 		}
 		write_buf(f,pattern,l);
-	}    
+	}
 
 	write_int(f,0);
 }
 
 
 void recv_exclude_list(int f)
