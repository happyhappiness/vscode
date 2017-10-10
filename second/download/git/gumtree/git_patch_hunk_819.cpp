 			die(_("Couldn't look up commit object for HEAD"));
 	}
 	for (i = 0; i < argc; i++, strbuf_release(&bname)) {
 		char *target = NULL;
 		int flags = 0;
 
-		strbuf_branchname(&bname, argv[i]);
+		strbuf_branchname(&bname, argv[i], allowed_interpret);
 		free(name);
 		name = mkpathdup(fmt, bname.buf);
 
 		if (kinds == FILTER_REFS_BRANCHES) {
 			const struct worktree *wt =
 				find_shared_symref("HEAD", name);
