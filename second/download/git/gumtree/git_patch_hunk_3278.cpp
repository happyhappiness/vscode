 	}
 	for (i = 0; i < argc; i++, strbuf_release(&bname)) {
 		const char *target;
 		int flags = 0;
 
 		strbuf_branchname(&bname, argv[i]);
-		if (kinds == FILTER_REFS_BRANCHES && !strcmp(head, bname.buf)) {
-			error(_("Cannot delete the branch '%s' "
-			      "which you are currently on."), bname.buf);
-			ret = 1;
-			continue;
-		}
-
 		free(name);
-
 		name = mkpathdup(fmt, bname.buf);
+
+		if (kinds == FILTER_REFS_BRANCHES) {
+			char *worktree = find_shared_symref("HEAD", name);
+			if (worktree) {
+				error(_("Cannot delete branch '%s' "
+					"checked out at '%s'"),
+				      bname.buf, worktree);
+				free(worktree);
+				ret = 1;
+				continue;
+			}
+		}
+
 		target = resolve_ref_unsafe(name,
 					    RESOLVE_REF_READING
 					    | RESOLVE_REF_NO_RECURSE
 					    | RESOLVE_REF_ALLOW_BAD_NAME,
 					    sha1, &flags);
 		if (!target) {
