 		}
 	}
 
 	if (!(ret = new0(struct filter_struct)))
 		out_of_memory("add_rule");
 
+	if (pat_len > 1 && pat[pat_len-1] == '/') {
+		pat_len--;
+		mflags |= MATCHFLG_DIRECTORY;
+	}
+
+	for (cp = pat; cp < pat + pat_len; cp++) {
+		if (*cp == '/')
+			slash_cnt++;
+	}
+
 	if (!(mflags & (MATCHFLG_ABS_PATH | MATCHFLG_MERGE_FILE))
 	 && ((xflags & (XFLG_ANCHORED2ABS|XFLG_ABS_IF_SLASH) && *pat == '/')
-	  || (xflags & XFLG_ABS_IF_SLASH && strchr(pat, '/') != NULL))) {
+	  || (xflags & XFLG_ABS_IF_SLASH && slash_cnt))) {
 		mflags |= MATCHFLG_ABS_PATH;
 		if (*pat == '/')
-			ex_len = dirbuf_len - module_dirlen - 1;
+			pre_len = dirbuf_len - module_dirlen - 1;
 		else
-			ex_len = 0;
+			pre_len = 0;
+	} else
+		pre_len = 0;
+
+	/* The daemon wants dir-exclude rules to get an appended "/" + "***". */
+	if (xflags & XFLG_DIR2WILD3
+	 && BITS_SETnUNSET(mflags, MATCHFLG_DIRECTORY, MATCHFLG_INCLUDE)) {
+		mflags &= ~MATCHFLG_DIRECTORY;
+		suf_len = sizeof SLASH_WILD3_SUFFIX - 1;
 	} else
-		ex_len = 0;
-	if (!(ret->pattern = new_array(char, ex_len + pat_len + 1)))
+		suf_len = 0;
+
+	if (!(ret->pattern = new_array(char, pre_len + pat_len + suf_len + 1)))
 		out_of_memory("add_rule");
-	if (ex_len)
-		memcpy(ret->pattern, dirbuf + module_dirlen, ex_len);
-	strlcpy(ret->pattern + ex_len, pat, pat_len + 1);
-	pat_len += ex_len;
+	if (pre_len) {
+		memcpy(ret->pattern, dirbuf + module_dirlen, pre_len);
+		for (cp = ret->pattern; cp < ret->pattern + pre_len; cp++) {
+			if (*cp == '/')
+				slash_cnt++;
+		}
+	}
+	strlcpy(ret->pattern + pre_len, pat, pat_len + 1);
+	pat_len += pre_len;
+	if (suf_len) {
+		memcpy(ret->pattern + pat_len, SLASH_WILD3_SUFFIX, suf_len+1);
+		pat_len += suf_len;
+		slash_cnt++;
+	}
 
 	if (strpbrk(ret->pattern, "*[?")) {
 		mflags |= MATCHFLG_WILD;
 		if ((cp = strstr(ret->pattern, "**")) != NULL) {
 			mflags |= MATCHFLG_WILD2;
 			/* If the pattern starts with **, note that. */
