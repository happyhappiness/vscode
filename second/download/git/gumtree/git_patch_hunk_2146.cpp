 	negative = do_match_pathspec(ps, name, namelen,
 				     prefix, seen,
 				     flags | DO_MATCH_EXCLUDE);
 	return negative ? 0 : positive;
 }
 
+int report_path_error(const char *ps_matched,
+		      const struct pathspec *pathspec,
+		      const char *prefix)
+{
+	/*
+	 * Make sure all pathspec matched; otherwise it is an error.
+	 */
+	struct strbuf sb = STRBUF_INIT;
+	int num, errors = 0;
+	for (num = 0; num < pathspec->nr; num++) {
+		int other, found_dup;
+
+		if (ps_matched[num])
+			continue;
+		/*
+		 * The caller might have fed identical pathspec
+		 * twice.  Do not barf on such a mistake.
+		 * FIXME: parse_pathspec should have eliminated
+		 * duplicate pathspec.
+		 */
+		for (found_dup = other = 0;
+		     !found_dup && other < pathspec->nr;
+		     other++) {
+			if (other == num || !ps_matched[other])
+				continue;
+			if (!strcmp(pathspec->items[other].original,
+				    pathspec->items[num].original))
+				/*
+				 * Ok, we have a match already.
+				 */
+				found_dup = 1;
+		}
+		if (found_dup)
+			continue;
+
+		error("pathspec '%s' did not match any file(s) known to git.",
+		      pathspec->items[num].original);
+		errors++;
+	}
+	strbuf_release(&sb);
+	return errors;
+}
+
 /*
  * Return the length of the "simple" part of a path match limiter.
  */
 int simple_length(const char *match)
 {
 	int len = -1;
