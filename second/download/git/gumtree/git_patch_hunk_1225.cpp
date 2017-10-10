 
 	if (write_cache_as_tree(tree.hash, 0, NULL))
 		die(_("git write-tree failed to write a tree"));
 
 	if (!get_sha1_commit("HEAD", parent.hash)) {
 		old_oid = &parent;
-		commit_list_insert(lookup_commit(parent.hash), &parents);
+		commit_list_insert(lookup_commit(&parent), &parents);
 	} else {
 		old_oid = NULL;
 		say(state, stderr, _("applying to an empty history"));
 	}
 
 	author = fmt_ident(state->author_name, state->author_email,
