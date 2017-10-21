 
 struct exclude_list_struct exclude_list = { 0, 0, "" };
 struct exclude_list_struct local_exclude_list = { 0, 0, "per-dir .cvsignore " };
 struct exclude_list_struct server_exclude_list = { 0, 0, "server " };
 char *exclude_path_prefix = NULL;
 
-/** Build an exclude structure given a exclude pattern */
-static void make_exclude(struct exclude_list_struct *listp, const char *pattern,
-			 int pat_len, int include)
+/** Build an exclude structure given an exclude pattern. */
+static void make_exclude(struct exclude_list_struct *listp, const char *pat,
+			 unsigned int pat_len, unsigned int mflags)
 {
 	struct exclude_struct *ret;
 	const char *cp;
-	int ex_len;
+	unsigned int ex_len;
 
 	ret = new(struct exclude_struct);
 	if (!ret)
 		out_of_memory("make_exclude");
 
 	memset(ret, 0, sizeof ret[0]);
-	ret->include = include;
 
 	if (exclude_path_prefix)
-		ret->match_flags |= MATCHFLG_ABS_PATH;
-	if (exclude_path_prefix && *pattern == '/')
+		mflags |= MATCHFLG_ABS_PATH;
+	if (exclude_path_prefix && *pat == '/')
 		ex_len = strlen(exclude_path_prefix);
 	else
 		ex_len = 0;
 	ret->pattern = new_array(char, ex_len + pat_len + 1);
 	if (!ret->pattern)
 		out_of_memory("make_exclude");
 	if (ex_len)
 		memcpy(ret->pattern, exclude_path_prefix, ex_len);
-	strlcpy(ret->pattern + ex_len, pattern, pat_len + 1);
+	strlcpy(ret->pattern + ex_len, pat, pat_len + 1);
 	pat_len += ex_len;
 
 	if (strpbrk(ret->pattern, "*[?")) {
-		ret->match_flags |= MATCHFLG_WILD;
+		mflags |= MATCHFLG_WILD;
 		if ((cp = strstr(ret->pattern, "**")) != NULL) {
-			ret->match_flags |= MATCHFLG_WILD2;
+			mflags |= MATCHFLG_WILD2;
 			/* If the pattern starts with **, note that. */
 			if (cp == ret->pattern)
-				ret->match_flags |= MATCHFLG_WILD2_PREFIX;
+				mflags |= MATCHFLG_WILD2_PREFIX;
 		}
 	}
 
 	if (pat_len > 1 && ret->pattern[pat_len-1] == '/') {
 		ret->pattern[pat_len-1] = 0;
-		ret->directory = 1;
+		mflags |= MATCHFLG_DIRECTORY;
 	}
 
 	for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
 		ret->slash_cnt++;
 
+	ret->match_flags = mflags;
+
 	if (!listp->tail)
 		listp->head = listp->tail = ret;
 	else {
 		listp->tail->next = ret;
 		listp->tail = ret;
 	}
