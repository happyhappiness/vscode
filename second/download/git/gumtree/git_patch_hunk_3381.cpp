 		die(_("'%s' already exists"), path);
 
 	/* is 'refname' a branch or commit? */
 	if (!opts->detach && !strbuf_check_branch_ref(&symref, refname) &&
 		 ref_exists(symref.buf)) { /* it's a branch */
 		if (!opts->force)
-			die_if_checked_out(symref.buf);
+			die_if_checked_out(symref.buf, 0);
 	} else { /* must be a commit */
 		commit = lookup_commit_reference_by_name(refname);
 		if (!commit)
 			die(_("invalid reference: %s"), refname);
 	}
 
