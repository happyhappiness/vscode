 	if (states.stale.nr) {
 		printf_ln(_("Pruning %s"), remote);
 		printf_ln(_("URL: %s"),
 		       states.remote->url_nr
 		       ? states.remote->url[0]
 		       : _("(no URL)"));
+
+		delete_refs = xmalloc(states.stale.nr * sizeof(*delete_refs));
+		for (i = 0; i < states.stale.nr; i++)
+			delete_refs[i] = states.stale.items[i].util;
+		if (!dry_run)
+			result |= repack_without_refs(delete_refs, states.stale.nr);
+		free(delete_refs);
 	}
 
 	for (i = 0; i < states.stale.nr; i++) {
 		const char *refname = states.stale.items[i].util;
 
+		string_list_insert(&delete_refs_list, refname);
+
 		if (!dry_run)
 			result |= delete_ref(refname, NULL, 0);
 
 		if (dry_run)
 			printf_ln(_(" * [would prune] %s"),
 			       abbrev_ref(refname, "refs/remotes/"));
 		else
 			printf_ln(_(" * [pruned] %s"),
 			       abbrev_ref(refname, "refs/remotes/"));
-		warn_dangling_symref(stdout, dangling_msg, refname);
 	}
 
+	warn_dangling_symrefs(stdout, dangling_msg, &delete_refs_list);
+	string_list_clear(&delete_refs_list, 0);
+
 	free_remote_ref_states(&states);
 	return result;
 }
 
 static int prune(int argc, const char **argv)
 {
