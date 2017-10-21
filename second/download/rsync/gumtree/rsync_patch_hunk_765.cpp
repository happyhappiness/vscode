 	*dest = '\0';
 	va_end(ap);
 
 	return ret;
 }
 
-void clean_fname(char *name)
+int count_dir_elements(const char *p)
 {
-	char *p;
-	int l;
-	int modified = 1;
+	int cnt = 0, new_component = 1;
+	while (*p) {
+		if (*p++ == '/')
+			new_component = 1;
+		else if (new_component) {
+			new_component = 0;
+			cnt++;
+		}
+	}
+	return cnt;
+}
 
-	if (!name) return;
+/* Turns multiple adjacent slashes into a single slash, gets rid of "./"
+ * elements (but not a trailing dot dir), removes a trailing slash, and
+ * optionally collapses ".." elements (except for those at the start of the
+ * string).  If the resulting name would be empty, change it into a ".". */
+unsigned int clean_fname(char *name, BOOL collapse_dot_dot)
+{
+	char *limit = name - 1, *t = name, *f = name;
+	int anchored;
 
-	while (modified) {
-		modified = 0;
+	if (!name)
+		return 0;
 
-		if ((p = strstr(name,"/./")) != NULL) {
-			modified = 1;
-			while (*p) {
-				p[0] = p[2];
-				p++;
-			}
+	if ((anchored = *f == '/') != 0)
+		*t++ = *f++;
+	while (*f) {
+		/* discard extra slashes */
+		if (*f == '/') {
+			f++;
+			continue;
 		}
-
-		if ((p = strstr(name,"//")) != NULL) {
-			modified = 1;
-			while (*p) {
-				p[0] = p[1];
-				p++;
+		if (*f == '.') {
+			/* discard "." dirs (but NOT a trailing '.'!) */
+			if (f[1] == '/') {
+				f += 2;
+				continue;
+			}
+			/* collapse ".." dirs */
+			if (collapse_dot_dot
+			    && f[1] == '.' && (f[2] == '/' || !f[2])) {
+				char *s = t - 1;
+				if (s == name && anchored) {
+					f += 2;
+					continue;
+				}
+				while (s > limit && *--s != '/') {}
+				if (s != t - 1 && (s < name || *s == '/')) {
+					t = s + 1;
+					f += 2;
+					continue;
+				}
+				limit = t + 2;
 			}
 		}
+		while (*f && (*t++ = *f++) != '/') {}
+	}
 
-		if (strncmp(p = name, "./", 2) == 0) {
-			modified = 1;
-			do {
-				p[0] = p[2];
-			} while (*p++);
-		}
+	if (t > name+anchored && t[-1] == '/')
+		t--;
+	if (t == name)
+		*t++ = '.';
+	*t = '\0';
 
-		l = strlen(p = name);
-		if (l > 1 && p[l-1] == '/') {
-			modified = 1;
-			p[l-1] = 0;
-		}
-	}
+	return t - name;
 }
 
-/**
- * Make path appear as if a chroot had occurred:
- *
- * @li 1. remove leading "/" (or replace with "." if at end)
- *
- * @li 2. remove leading ".." components (except those allowed by @p reldir)
+/* Make path appear as if a chroot had occurred.  This handles a leading
+ * "/" (either removing it or expanding it) and any leading or embedded
+ * ".." components that attempt to escape past the module's top dir.
  *
- * @li 3. delete any other "<dir>/.." (recursively)
+ * If dest is NULL, a buffer is allocated to hold the result.  It is legal
+ * to call with the dest and the path (p) pointing to the same buffer, but
+ * rootdir will be ignored to avoid expansion of the string.
  *
- * Can only shrink paths, so sanitizes in place.
+ * The rootdir string contains a value to use in place of a leading slash.
+ * Specify NULL to get the default of lp_path(module_id).
  *
- * While we're at it, remove double slashes and "." components like
- *   clean_fname() does, but DON'T remove a trailing slash because that
- *   is sometimes significant on command line arguments.
+ * If depth is >= 0, it is a count of how many '..'s to allow at the start
+ * of the path.  Use -1 to allow unlimited depth.
  *
- * If @p reldir is non-null, it is a sanitized directory that the path will be
- *    relative to, so allow as many ".." at the beginning of the path as
- *    there are components in reldir.  This is used for symbolic link targets.
- *    If reldir is non-null and the path began with "/", to be completely like
- *    a chroot we should add in depth levels of ".." at the beginning of the
- *    path, but that would blow the assumption that the path doesn't grow and
- *    it is not likely to end up being a valid symlink anyway, so just do
- *    the normal removal of the leading "/" instead.
+ * We also clean the path in a manner similar to clean_fname() but with a
+ * few differences: 
  *
- * Contributed by Dave Dykstra <dwd@bell-labs.com>
- */
-void sanitize_path(char *p, char *reldir)
+ * Turns multiple adjacent slashes into a single slash, gets rid of "." dir
+ * elements (INCLUDING a trailing dot dir), PRESERVES a trailing slash, and
+ * ALWAYS collapses ".." elements (except for those at the start of the
+ * string up to "depth" deep).  If the resulting name would be empty,
+ * change it into a ".". */
+char *sanitize_path(char *dest, const char *p, const char *rootdir, int depth)
 {
 	char *start, *sanp;
-	int depth = 0;
-	int allowdotdot = 0;
+	int rlen = 0;
 
-	if (reldir) {
-		depth++;
-		while (*reldir) {
-			if (*reldir++ == '/') {
-				depth++;
-			}
+	if (dest != p) {
+		int plen = strlen(p);
+		if (*p == '/') {
+			if (!rootdir)
+				rootdir = lp_path(module_id);
+			rlen = strlen(rootdir);
+			depth = 0;
+			p++;
+		}
+		if (dest) {
+			if (rlen + plen + 1 >= MAXPATHLEN)
+				return NULL;
+		} else if (!(dest = new_array(char, rlen + plen + 1)))
+			out_of_memory("sanitize_path");
+		if (rlen) {
+			memcpy(dest, rootdir, rlen);
+			if (rlen > 1)
+				dest[rlen++] = '/';
 		}
 	}
-	start = p;
-	sanp = p;
-	while (*p == '/') {
-		/* remove leading slashes */
-		p++;
-	}
+
+	start = sanp = dest + rlen;
 	while (*p != '\0') {
+		/* discard leading or extra slashes */
+		if (*p == '/') {
+			p++;
+			continue;
+		}
 		/* this loop iterates once per filename component in p.
 		 * both p (and sanp if the original had a slash) should
 		 * always be left pointing after a slash
 		 */
 		if (*p == '.' && (p[1] == '/' || p[1] == '\0')) {
 			/* skip "." component */
-			while (*++p == '/') {
-				/* skip following slashes */
-				;
-			}
+			p++;
 			continue;
 		}
-		allowdotdot = 0;
 		if (*p == '.' && p[1] == '.' && (p[2] == '/' || p[2] == '\0')) {
 			/* ".." component followed by slash or end */
-			if (depth > 0 && sanp == start) {
-				/* allow depth levels of .. at the beginning */
-				--depth;
-				allowdotdot = 1;
-			} else {
+			if (depth <= 0 || sanp != start) {
 				p += 2;
-				if (*p == '/')
-					p++;
 				if (sanp != start) {
 					/* back up sanp one level */
 					--sanp; /* now pointing at slash */
 					while (sanp > start && sanp[-1] != '/') {
 						/* skip back up to slash */
 						sanp--;
 					}
 				}
 				continue;
 			}
-		}
-		while (1) {
-			/* copy one component through next slash */
-			*sanp++ = *p++;
-			if (*p == '\0' || p[-1] == '/') {
-				while (*p == '/') {
-					/* skip multiple slashes */
-					p++;
-				}
-				break;
-			}
-		}
-		if (allowdotdot) {
+			/* allow depth levels of .. at the beginning */
+			depth--;
 			/* move the virtual beginning to leave the .. alone */
-			start = sanp;
+			start = sanp + 3;
 		}
+		/* copy one component through next slash */
+		while (*p && (*sanp++ = *p++) != '/') {}
 	}
-	if (sanp == start && !allowdotdot) {
+	if (sanp == dest) {
 		/* ended up with nothing, so put in "." component */
-		/*
-		 * note that the !allowdotdot doesn't prevent this from
-		 *  happening in all allowed ".." situations, but I didn't
-		 *  think it was worth putting in an extra variable to ensure
-		 *  it since an extra "." won't hurt in those situations.
-		 */
 		*sanp++ = '.';
 	}
 	*sanp = '\0';
-}
 
-/* Works much like sanitize_path(), with these differences:  (1) a new buffer
- * is allocated for the sanitized path rather than modifying it in-place; (2)
- * a leading slash gets transformed into the rootdir value (which can be empty
- * or NULL if you just want the slash to get dropped); (3) no "reldir" can be
- * specified. */
-char *alloc_sanitize_path(const char *path, const char *rootdir)
-{
-	char *buf;
-	int rlen, plen = strlen(path);
-
-	if (*path == '/' && rootdir) {
-		rlen = strlen(rootdir);
-		if (rlen == 1)
-			path++;
-	} else
-		rlen = 0;
-	if (!(buf = new_array(char, rlen + plen + 1)))
-		out_of_memory("alloc_sanitize_path");
-	if (rlen)
-		memcpy(buf, rootdir, rlen);
-	memcpy(buf + rlen, path, plen + 1);
-
-	if (rlen > 1)
-		rlen++;
-	sanitize_path(buf + rlen, NULL);
-	if (rlen && buf[rlen] == '.' && buf[rlen+1] == '\0') {
-		if (rlen > 1)
-			rlen--;
-		buf[rlen] = '\0';
-	}
-
-	return buf;
+	return dest;
 }
 
 char curr_dir[MAXPATHLEN];
 unsigned int curr_dir_len;
 
 /**
