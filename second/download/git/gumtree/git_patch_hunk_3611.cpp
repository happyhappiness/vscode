 			++nr;
 		}
 	}
 	die_errno(_("unable to write file '%s' mode %o"), path, mode);
 }
 
-static void add_conflicted_stages_file(struct patch *patch)
+static void add_conflicted_stages_file(struct apply_state *state,
+				       struct patch *patch)
 {
 	int stage, namelen;
 	unsigned ce_size, mode;
 	struct cache_entry *ce;
 
-	if (!update_index)
+	if (!state->update_index)
 		return;
 	namelen = strlen(patch->new_name);
 	ce_size = cache_entry_size(namelen);
 	mode = patch->new_mode ? patch->new_mode : (S_IFREG | 0644);
 
 	remove_file_from_cache(patch->new_name);
