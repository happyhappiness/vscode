 	unsigned char sha1[20];
 	if (write_sha1_file("", 0, blob_type, sha1))
 		die("cannot create an empty blob in the object database");
 	hashcpy(ce->sha1, sha1);
 }
 
-int add_to_index(struct index_state *istate, const char *path, struct stat *st, int flags)
+int add_to_index(struct index_state *istate, const char *path, struct stat *st, int flags, int force_mode)
 {
 	int size, namelen, was_same;
 	mode_t st_mode = st->st_mode;
 	struct cache_entry *ce, *alias;
 	unsigned ce_option = CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE|CE_MATCH_RACY_IS_DIRTY;
 	int verbose = flags & (ADD_CACHE_VERBOSE | ADD_CACHE_PRETEND);
