 {
 	struct commit *current = NULL, *updated;
 	enum object_type type;
 	struct branch *current_branch = branch_get(NULL);
 	const char *pretty_ref = prettify_refname(ref->name);
 
-	type = sha1_object_info(ref->new_sha1, NULL);
+	type = sha1_object_info(ref->new_oid.hash, NULL);
 	if (type < 0)
-		die(_("object %s not found"), sha1_to_hex(ref->new_sha1));
+		die(_("object %s not found"), oid_to_hex(&ref->new_oid));
 
-	if (!hashcmp(ref->old_sha1, ref->new_sha1)) {
+	if (!oidcmp(&ref->old_oid, &ref->new_oid)) {
 		if (verbosity > 0)
 			strbuf_addf(display, "= %-*s %-*s -> %s",
 				    TRANSPORT_SUMMARY(_("[up to date]")),
 				    REFCOL_WIDTH, remote, pretty_ref);
 		return 0;
 	}
 
 	if (current_branch &&
 	    !strcmp(ref->name, current_branch->name) &&
 	    !(update_head_ok || is_bare_repository()) &&
-	    !is_null_sha1(ref->old_sha1)) {
+	    !is_null_oid(&ref->old_oid)) {
 		/*
 		 * If this is the head, and it's not okay to update
 		 * the head, and the old value of the head isn't empty...
 		 */
 		strbuf_addf(display,
 			    _("! %-*s %-*s -> %s  (can't fetch in current branch)"),
 			    TRANSPORT_SUMMARY(_("[rejected]")),
 			    REFCOL_WIDTH, remote, pretty_ref);
 		return 1;
 	}
 
-	if (!is_null_sha1(ref->old_sha1) &&
+	if (!is_null_oid(&ref->old_oid) &&
 	    starts_with(ref->name, "refs/tags/")) {
 		int r;
 		r = s_update_ref("updating tag", ref, 0);
 		strbuf_addf(display, "%c %-*s %-*s -> %s%s",
 			    r ? '!' : '-',
 			    TRANSPORT_SUMMARY(_("[tag update]")),
 			    REFCOL_WIDTH, remote, pretty_ref,
 			    r ? _("  (unable to update local ref)") : "");
 		return r;
 	}
 
-	current = lookup_commit_reference_gently(ref->old_sha1, 1);
-	updated = lookup_commit_reference_gently(ref->new_sha1, 1);
+	current = lookup_commit_reference_gently(ref->old_oid.hash, 1);
+	updated = lookup_commit_reference_gently(ref->new_oid.hash, 1);
 	if (!current || !updated) {
 		const char *msg;
 		const char *what;
 		int r;
 		/*
 		 * Nicely describe the new ref we're fetching.
