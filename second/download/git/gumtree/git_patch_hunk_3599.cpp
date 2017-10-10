 	}
 	return ce_match_stat(ce, st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
 }
 
 #define SUBMODULE_PATCH_WITHOUT_INDEX 1
 
-static int load_patch_target(struct strbuf *buf,
+static int load_patch_target(struct apply_state *state,
+			     struct strbuf *buf,
 			     const struct cache_entry *ce,
 			     struct stat *st,
 			     const char *name,
 			     unsigned expected_mode)
 {
-	if (cached || check_index) {
+	if (state->cached || state->check_index) {
 		if (read_file_or_gitlink(ce, buf))
-			return error(_("read of %s failed"), name);
+			return error(_("failed to read %s"), name);
 	} else if (name) {
 		if (S_ISGITLINK(expected_mode)) {
 			if (ce)
 				return read_file_or_gitlink(ce, buf);
 			else
 				return SUBMODULE_PATCH_WITHOUT_INDEX;
 		} else if (has_symlink_leading_path(name, strlen(name))) {
 			return error(_("reading from '%s' beyond a symbolic link"), name);
 		} else {
 			if (read_old_data(st, name, buf))
-				return error(_("read of %s failed"), name);
+				return error(_("failed to read %s"), name);
 		}
 	}
 	return 0;
 }
 
 /*
  * We are about to apply "patch"; populate the "image" with the
  * current version we have, from the working tree or from the index,
  * depending on the situation e.g. --cached/--index.  If we are
  * applying a non-git patch that incrementally updates the tree,
  * we read from the result of a previous diff.
  */
-static int load_preimage(struct image *image,
+static int load_preimage(struct apply_state *state,
+			 struct image *image,
 			 struct patch *patch, struct stat *st,
 			 const struct cache_entry *ce)
 {
 	struct strbuf buf = STRBUF_INIT;
 	size_t len;
 	char *img;
 	struct patch *previous;
 	int status;
 
-	previous = previous_patch(patch, &status);
+	previous = previous_patch(state, patch, &status);
 	if (status)
 		return error(_("path %s has been renamed/deleted"),
 			     patch->old_name);
 	if (previous) {
 		/* We have a patched copy in memory; use that. */
 		strbuf_add(&buf, previous->result, previous->resultsize);
 	} else {
-		status = load_patch_target(&buf, ce, st,
+		status = load_patch_target(state, &buf, ce, st,
 					   patch->old_name, patch->old_mode);
 		if (status < 0)
 			return status;
 		else if (status == SUBMODULE_PATCH_WITHOUT_INDEX) {
 			/*
 			 * There is no way to apply subproject
