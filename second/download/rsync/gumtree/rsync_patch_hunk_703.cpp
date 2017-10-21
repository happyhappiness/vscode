 	return 0;
 }
 
 
 static void report_exclude_result(char const *name,
                                   struct exclude_struct const *ent,
-                                  int name_is_dir)
+                                  int name_is_dir, const char *type)
 {
 	/* If a trailing slash is present to match only directories,
 	 * then it is stripped out by make_exclude.  So as a special
 	 * case we add it back in here. */
 
-	if (verbose >= 2)
-		rprintf(FINFO, "%s %s %s because of pattern %s%s\n",
-			ent->include ? "including" : "excluding",
-			name_is_dir ? "directory" : "file",
-			name, ent->pattern,
-			ent->directory ? "/" : "");
+	if (verbose >= 2) {
+		rprintf(FINFO, "[%s] %scluding %s %s because of %spattern %s%s\n",
+			who_am_i(), ent->include ? "in" : "ex",
+			name_is_dir ? "directory" : "file", name, type,
+			ent->pattern, ent->directory ? "/" : "");
+	}
 }
 
 
 /*
- * Return true if file NAME is defined to be excluded by either
- * LOCAL_EXCLUDE_LIST or the globals EXCLUDE_LIST.
+ * Return -1 if file "name" is defined to be excluded by the specified
+ * exclude list, 1 if it is included, and 0 if it was not matched.
  */
-int check_exclude(struct exclude_struct **list, char *name, int name_is_dir)
+int check_exclude(struct exclude_list_struct *listp, char *name, int name_is_dir)
 {
 	struct exclude_struct *ent;
 
-	while ((ent = *list++) != NULL) {
+	for (ent = listp->head; ent; ent = ent->next) {
 		if (check_one_exclude(name, ent, name_is_dir)) {
-			report_exclude_result(name, ent, name_is_dir);
-			return !ent->include;
+			report_exclude_result(name, ent, name_is_dir,
+					      listp->debug_type);
+			return ent->include ? 1 : -1;
 		}
 	}
 
 	return 0;
 }
 
 
-void add_exclude(struct exclude_struct ***listp, const char *pattern, int include)
+/* Get the next include/exclude arg from the string.  The token will not
+ * be '\0' terminated, so use the returned length to limit the string.
+ * Also, be sure to add this length to the returned pointer before passing
+ * it back to ask for the next token.  This routine will not parse the +/-
+ * prefixes or the "!" token when xflags contains XFLG_WORDS_ONLY.  The
+ * *incl_ptr value will be 1 for an include, 0 for an exclude, and -1 for
+ * the list-clearing "!" token.
+ */
+static const char *get_exclude_tok(const char *p, int *len_ptr, int *incl_ptr,
+				   int xflags)
 {
-	struct exclude_struct **list = *listp;
-	int len = 0;
+	const unsigned char *s = (const unsigned char *)p;
+	int len;
 
-	if (*pattern == '!' && !pattern[1]) {
-	    free_exclude_list(listp);
-	    return;
+	if (xflags & XFLG_WORD_SPLIT) {
+		/* Skip over any initial whitespace. */
+		while (isspace(*s))
+			s++;
+		/* Update for "!" check. */
+		p = (const char *)s;
 	}
 
-	if (list)
-		for (; list[len]; len++) {}
+	/* Is this a '+' or '-' followed by a space (not whitespace)? */
+	if (!(xflags & XFLG_WORDS_ONLY)
+	    && (*s == '-' || *s == '+') && s[1] == ' ') {
+		*incl_ptr = *s == '+';
+		s += 2;
+	} else
+		*incl_ptr = xflags & XFLG_DEF_INCLUDE;
 
- 	list = *listp = realloc_array(list, struct exclude_struct *, len+2);
+	if (xflags & XFLG_WORD_SPLIT) {
+		const unsigned char *cp = s;
+		/* Token ends at whitespace or the end of the string. */
+		while (!isspace(*cp) && *cp != '\0')
+			cp++;
+		len = cp - s;
+	} else
+		len = strlen(s);
 
-	if (!list || !(list[len] = make_exclude(pattern, include)))
-		out_of_memory("add_exclude");
+	if (*p == '!' && len == 1 && !(xflags & XFLG_WORDS_ONLY))
+		*incl_ptr = -1;
 
-	if (verbose > 2) {
-		rprintf(FINFO,"add_exclude(%s,%s)\n",pattern,
-			include ? "include" : "exclude");
-	}
+	*len_ptr = len;
+	return (const char *)s;
+}
 
-	list[len+1] = NULL;
+
+void add_exclude(struct exclude_list_struct *listp, const char *pattern,
+		 int xflags)
+{
+	int pat_len, incl;
+	const char *cp;
+
+	if (!pattern)
+		return;
+
+	cp = pattern;
+	pat_len = 0;
+	while (1) {
+		cp = get_exclude_tok(cp + pat_len, &pat_len, &incl, xflags);
+		if (!pat_len)
+			break;
+		/* If we got the special "!" token, clear the list. */
+		if (incl < 0)
+			free_exclude_list(listp);
+		else {
+			make_exclude(listp, cp, pat_len, incl);
+
+			if (verbose > 2) {
+				rprintf(FINFO, "[%s] add_exclude(%.*s, %s%s)\n",
+					who_am_i(), pat_len, cp,
+					listp->debug_type,
+					incl ? "include" : "exclude");
+			}
+		}
+	}
 }
 
 
-void add_exclude_file(struct exclude_struct ***listp, const char *fname,
-		      int fatal, int include)
+void add_exclude_file(struct exclude_list_struct *listp, const char *fname,
+		      int xflags)
 {
-	int fd;
+	FILE *fp;
 	char line[MAXPATHLEN];
 	char *eob = line + MAXPATHLEN - 1;
-	extern int eol_nulls;
+	int word_split = xflags & XFLG_WORD_SPLIT;
 
 	if (!fname || !*fname)
 		return;
 
 	if (*fname != '-' || fname[1])
-		fd = open(fname, O_RDONLY|O_BINARY);
+		fp = fopen(fname, "rb");
 	else
-		fd = 0;
-	if (fd < 0) {
-		if (fatal) {
+		fp = stdin;
+	if (!fp) {
+		if (xflags & XFLG_FATAL_ERRORS) {
 			rsyserr(FERROR, errno,
 				"failed to open %s file %s",
-				include ? "include" : "exclude",
+				xflags & XFLG_DEF_INCLUDE ? "include" : "exclude",
 				fname);
 			exit_cleanup(RERR_FILEIO);
 		}
 		return;
 	}
 
 	while (1) {
-		char ch, *s = line;
-		int cnt;
+		char *s = line;
+		int ch;
 		while (1) {
-			if ((cnt = read(fd, &ch, 1)) <= 0) {
-				if (cnt < 0 && errno == EINTR)
+			if ((ch = getc(fp)) == EOF) {
+				if (ferror(fp) && errno == EINTR)
 					continue;
 				break;
 			}
+			if (word_split && isspace(ch))
+				break;
 			if (eol_nulls? !ch : (ch == '\n' || ch == '\r'))
 				break;
 			if (s < eob)
 				*s++ = ch;
 		}
 		*s = '\0';
-		if (*line && *line != ';' && *line != '#') {
-			/* Skip lines starting with semicolon or pound.
-			 * It probably wouldn't cause any harm to not skip
-			 * them but there's no need to save them. */
-			add_exclude(listp, line, include);
-		}
-		if (cnt <= 0)
+		/* Skip an empty token and (when line parsing) comments. */
+		if (*line && (word_split || (*line != ';' && *line != '#')))
+			add_exclude(listp, line, xflags);
+		if (ch == EOF)
 			break;
 	}
-	close(fd);
+	fclose(fp);
 }
 
 
 void send_exclude_list(int f)
 {
-	int i;
-	extern int protocol_version;
-	extern int list_only, recurse;
+	struct exclude_struct *ent;
 
 	/* This is a complete hack - blame Rusty.
 	 *
 	 * FIXME: This pattern shows up in the output of
 	 * report_exclude_result(), which is not ideal. */
 	if (list_only && !recurse)
-		add_exclude(&exclude_list, "/*/*", ADD_EXCLUDE);
+		add_exclude(&exclude_list, "/*/*", 0);
 
-	if (!exclude_list) {
-		write_int(f,0);
-		return;
-	}
-
-	for (i=0;exclude_list[i];i++) {
-		int l;
-		char pattern[MAXPATHLEN];
-
-		strlcpy(pattern,exclude_list[i]->pattern,sizeof(pattern));
-		if (exclude_list[i]->directory) strlcat(pattern,"/", sizeof(pattern));
-
-		l = strlen(pattern);
-		if (l == 0) continue;
-		if (exclude_list[i]->include) {
-			if (protocol_version < 19) {
-				rprintf(FERROR,"remote rsync does not support include syntax - aborting\n");
-				exit_cleanup(RERR_UNSUPPORTED);
-			}
-			write_int(f,l+2);
-			write_buf(f,"+ ",2);
-		} else {
-			write_int(f,l);
+	for (ent = exclude_list.head; ent; ent = ent->next) {
+		unsigned int l;
+		char p[MAXPATHLEN+1];
+
+		l = strlcpy(p, ent->pattern, sizeof p);
+		if (l == 0 || l >= MAXPATHLEN)
+			continue;
+		if (ent->directory) {
+			p[l++] = '/';
+			p[l] = '\0';
 		}
-		write_buf(f,pattern,l);
+
+		if (ent->include) {
+			write_int(f, l + 2);
+			write_buf(f, "+ ", 2);
+		} else if ((*p == '-' || *p == '+') && p[1] == ' ') {
+			write_int(f, l + 2);
+			write_buf(f, "- ", 2);
+		} else
+			write_int(f, l);
+		write_buf(f, p, l);
 	}
 
-	write_int(f,0);
+	write_int(f, 0);
 }
 
 
 void recv_exclude_list(int f)
 {
-	char line[MAXPATHLEN];
+	char line[MAXPATHLEN+1]; /* Allows a trailing slash on a max-len dir */
 	unsigned int l;
 
-	while ((l=read_int(f))) {
-		if (l >= MAXPATHLEN) overflow("recv_exclude_list");
-		read_sbuf(f,line,l);
-		add_exclude(&exclude_list, line, ADD_EXCLUDE);
-	}
-}
-
-/* Get the next include/exclude arg from the string. It works in a similar way
-** to strtok - initially an arg is sent over, from then on NULL. This
-** routine takes into account any +/- in the strings and does not
-** consider the space following it as a delimeter.
-*/
-char *get_exclude_tok(char *p)
-{
-	static char *s;
-	static int more;
-	char *t;
-
-	if (p) {
-		s=p;
-		if (*p)
-			more=1;
+	while ((l = read_int(f)) != 0) {
+		if (l >= sizeof line)
+			overflow("recv_exclude_list");
+		read_sbuf(f, line, l);
+		add_exclude(&exclude_list, line, 0);
 	}
-
-	if (!more)
-		return(NULL);
-
-	/* Skip over any initial spaces */
-	while (isspace(* (unsigned char *) s))
-		s++;
-
-	/* Are we at the end of the string? */
-	if (*s) {
-		/* remember the beginning of the token */
-		t=s;
-
-		/* Is this a '+' or '-' followed by a space (not whitespace)? */
-		if ((*s=='+' || *s=='-') && *(s+1)==' ')
-			s+=2;
-
-		/* Skip to the next space or the end of the string */
-		while (!isspace(* (unsigned char *) s) && *s != '\0')
-			s++;
-	} else {
-		t=NULL;
-	}
-
-	/* Have we reached the end of the string? */
-	if (*s)
-		*s++='\0';
-	else
-		more=0;
-	return(t);
 }
 
 
-void add_exclude_line(struct exclude_struct ***listp,
-		      const char *line, int include)
-{
-	char *tok, *p;
-	if (!line || !*line) return;
-	p = strdup(line);
-	if (!p) out_of_memory("add_exclude_line");
-	for (tok=get_exclude_tok(p); tok; tok=get_exclude_tok(NULL))
-		add_exclude(listp, tok, include);
-	free(p);
-}
-
-
-static char *cvs_ignore_list[] = {
-  "RCS/", "SCCS/", "CVS/", ".svn/", "CVS.adm", "RCSLOG", "cvslog.*",
-  "tags", "TAGS", ".make.state", ".nse_depinfo",
-  "*~", "#*", ".#*", ", *", "*.old", "*.bak", "*.BAK", "*.orig",
-  "*.rej", ".del-*", "*.a", "*.o", "*.obj", "*.so", "*.Z", "*.elc", "*.ln",
-  "core", NULL};
-
+static char default_cvsignore[] = 
+	/* These default ignored items come from the CVS manual. */
+	"RCS SCCS CVS CVS.adm RCSLOG cvslog.* tags TAGS"
+	" .make.state .nse_depinfo *~ #* .#* ,* _$* *$"
+	" *.old *.bak *.BAK *.orig *.rej .del-*"
+	" *.a *.olb *.o *.obj *.so *.exe"
+	" *.Z *.elc *.ln core"
+	/* The rest we added to suit ourself. */
+	" .svn/";
 
 void add_cvs_excludes(void)
 {
 	char fname[MAXPATHLEN];
 	char *p;
-	int i;
 
-	for (i=0; cvs_ignore_list[i]; i++)
-		add_exclude(&exclude_list, cvs_ignore_list[i], ADD_EXCLUDE);
+	add_exclude(&exclude_list, default_cvsignore,
+		    XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
 
-	if ((p=getenv("HOME")) && strlen(p) < (MAXPATHLEN-12)) {
-		snprintf(fname,sizeof(fname), "%s/.cvsignore",p);
-		add_exclude_file(&exclude_list,fname,MISSING_OK,ADD_EXCLUDE);
+	if ((p = getenv("HOME"))
+	    && pathjoin(fname, sizeof fname, p, ".cvsignore") < sizeof fname) {
+		add_exclude_file(&exclude_list, fname,
+				 XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
 	}
 
-	add_exclude_line(&exclude_list, getenv("CVSIGNORE"), ADD_EXCLUDE);
+	add_exclude(&exclude_list, getenv("CVSIGNORE"),
+		    XFLG_WORD_SPLIT | XFLG_WORDS_ONLY);
 }
