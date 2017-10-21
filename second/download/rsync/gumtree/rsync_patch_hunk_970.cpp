 	" *.old *.bak *.BAK *.orig *.rej .del-*"
 	" *.a *.olb *.o *.obj *.so *.exe"
 	" *.Z *.elc *.ln core"
 	/* The rest we added to suit ourself. */
 	" .svn/ .git/ .hg/ .bzr/";
 
-static void get_cvs_excludes(uint32 mflags)
+static void get_cvs_excludes(uint32 rflags)
 {
 	static int initialized = 0;
 	char *p, fname[MAXPATHLEN];
 
 	if (initialized)
 		return;
 	initialized = 1;
 
-	parse_rule(&cvs_filter_list, default_cvsignore,
-		   mflags | (protocol_version >= 30 ? MATCHFLG_PERISHABLE : 0),
-		   0);
+	parse_filter_str(&cvs_filter_list, default_cvsignore,
+			 rule_template(rflags | (protocol_version >= 30 ? FILTRULE_PERISHABLE : 0)),
+			 0);
 
 	p = module_id >= 0 && lp_use_chroot(module_id) ? "/" : getenv("HOME");
 	if (p && pathjoin(fname, MAXPATHLEN, p, ".cvsignore") < MAXPATHLEN)
-		parse_filter_file(&cvs_filter_list, fname, mflags, 0);
+		parse_filter_file(&cvs_filter_list, fname, rule_template(rflags), 0);
 
-	parse_rule(&cvs_filter_list, getenv("CVSIGNORE"), mflags, 0);
+	parse_filter_str(&cvs_filter_list, getenv("CVSIGNORE"), rule_template(rflags), 0);
 }
 
+const filter_rule *rule_template(uint32 rflags)
+{
+	static filter_rule template; /* zero-initialized */
+	template.rflags = rflags;
+	return &template;
+}
 
-void parse_rule(struct filter_list_struct *listp, const char *pattern,
-		uint32 mflags, int xflags)
+void parse_filter_str(filter_rule_list *listp, const char *rulestr,
+		     const filter_rule *template, int xflags)
 {
+	filter_rule *rule;
+	const char *pat;
 	unsigned int pat_len;
-	uint32 new_mflags;
-	const char *cp, *p;
 
-	if (!pattern)
+	if (!rulestr)
 		return;
 
 	while (1) {
+		uint32 new_rflags;
+
 		/* Remember that the returned string is NOT '\0' terminated! */
-		cp = parse_rule_tok(pattern, mflags, xflags,
-				    &pat_len, &new_mflags);
-		if (!cp)
+		if (!(rule = parse_rule_tok(&rulestr, template, xflags, &pat, &pat_len)))
 			break;
 
-		pattern = cp + pat_len;
-
 		if (pat_len >= MAXPATHLEN) {
 			rprintf(FERROR, "discarding over-long filter: %.*s\n",
-				(int)pat_len, cp);
+				(int)pat_len, pat);
+		    free_continue:
+			free_filter(rule);
 			continue;
 		}
 
-		if (new_mflags & MATCHFLG_CLEAR_LIST) {
-			if (verbose > 2) {
+		new_rflags = rule->rflags;
+		if (new_rflags & FILTRULE_CLEAR_LIST) {
+			if (DEBUG_GTE(FILTER, 2)) {
 				rprintf(FINFO,
 					"[%s] clearing filter list%s\n",
 					who_am_i(), listp->debug_type);
 			}
 			clear_filter_list(listp);
-			continue;
+			goto free_continue;
 		}
 
-		if (new_mflags & MATCHFLG_MERGE_FILE) {
-			unsigned int len;
+		if (new_rflags & FILTRULE_MERGE_FILE) {
 			if (!pat_len) {
-				cp = ".cvsignore";
+				pat = ".cvsignore";
 				pat_len = 10;
 			}
-			len = pat_len;
-			if (new_mflags & MATCHFLG_EXCLUDE_SELF) {
-				const char *name = cp + len;
-				while (name > cp && name[-1] != '/') name--;
-				len -= name - cp;
-				add_rule(listp, name, len, 0, 0);
-				new_mflags &= ~MATCHFLG_EXCLUDE_SELF;
-				len = pat_len;
+			if (new_rflags & FILTRULE_EXCLUDE_SELF) {
+				const char *name;
+				filter_rule *excl_self;
+
+				if (!(excl_self = new0(filter_rule)))
+					out_of_memory("parse_filter_str");
+				/* Find the beginning of the basename and add an exclude for it. */
+				for (name = pat + pat_len; name > pat && name[-1] != '/'; name--) {}
+				add_rule(listp, name, (pat + pat_len) - name, excl_self, 0);
+				rule->rflags &= ~FILTRULE_EXCLUDE_SELF;
 			}
-			if (new_mflags & MATCHFLG_PERDIR_MERGE) {
+			if (new_rflags & FILTRULE_PERDIR_MERGE) {
 				if (parent_dirscan) {
-					if (!(p = parse_merge_name(cp, &len,
-								module_dirlen)))
-						continue;
-					add_rule(listp, p, len, new_mflags, 0);
+					const char *p;
+					unsigned int len = pat_len;
+					if ((p = parse_merge_name(pat, &len, module_dirlen)))
+						add_rule(listp, p, len, rule, 0);
+					else
+						free_filter(rule);
 					continue;
 				}
 			} else {
-				if (!(p = parse_merge_name(cp, &len, 0)))
-					continue;
-				parse_filter_file(listp, p, new_mflags,
-						  XFLG_FATAL_ERRORS);
+				const char *p;
+				unsigned int len = pat_len;
+				if ((p = parse_merge_name(pat, &len, 0)))
+					parse_filter_file(listp, p, rule, XFLG_FATAL_ERRORS);
+				free_filter(rule);
 				continue;
 			}
 		}
 
-		add_rule(listp, cp, pat_len, new_mflags, xflags);
+		add_rule(listp, pat, pat_len, rule, xflags);
 
-		if (new_mflags & MATCHFLG_CVS_IGNORE
-		    && !(new_mflags & MATCHFLG_MERGE_FILE))
-			get_cvs_excludes(new_mflags);
+		if (new_rflags & FILTRULE_CVS_IGNORE
+		    && !(new_rflags & FILTRULE_MERGE_FILE))
+			get_cvs_excludes(new_rflags);
 	}
 }
 
-
-void parse_filter_file(struct filter_list_struct *listp, const char *fname,
-		       uint32 mflags, int xflags)
+void parse_filter_file(filter_rule_list *listp, const char *fname, const filter_rule *template, int xflags)
 {
 	FILE *fp;
 	char line[BIGPATHBUFLEN];
 	char *eob = line + sizeof line - 1;
-	int word_split = mflags & MATCHFLG_WORD_SPLIT;
+	BOOL word_split = (template->rflags & FILTRULE_WORD_SPLIT) != 0;
 
 	if (!fname || !*fname)
 		return;
 
 	if (*fname != '-' || fname[1] || am_server) {
 		if (daemon_filter_list.head) {
