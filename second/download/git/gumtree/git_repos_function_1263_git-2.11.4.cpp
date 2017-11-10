static int add_index_file(struct apply_state *state,
			   const char *path,
			   unsigned mode,
			   void *buf,
			   unsigned long size)
 {
	 struct stat st;
	 struct cache_entry *ce;
	 int namelen = strlen(path);
	 unsigned ce_size = cache_entry_size(namelen);

	 if (!state->update_index)
		 return 0;

	 ce = xcalloc(1, ce_size);
	 memcpy(ce->name, path, namelen);
	 ce->ce_mode = create_ce_mode(mode);
	 ce->ce_flags = create_ce_flags(0);
	 ce->ce_namelen = namelen;
	 if (S_ISGITLINK(mode)) {
		 const char *s;

		 if (!skip_prefix(buf, "Subproject commit ", &s) ||
		     get_oid_hex(s, &ce->oid)) {
			free(ce);
			return error(_("corrupt patch for submodule %s"), path);
		}
	} else {
		if (!state->cached) {
			if (lstat(path, &st) < 0) {
				free(ce);
				return error_errno(_("unable to stat newly "
						     "created file '%s'"),
						   path);
			}
			fill_stat_cache_info(ce, &st);
		}
		if (write_sha1_file(buf, size, blob_type, ce->oid.hash) < 0) {
			free(ce);
			return error(_("unable to create backing store "
				       "for newly created file %s"), path);
		}
	}
	if (add_cache_entry(ce, ADD_CACHE_OK_TO_ADD) < 0) {
		free(ce);
		return error(_("unable to add cache entry for %s"), path);
	}

	return 0;
}