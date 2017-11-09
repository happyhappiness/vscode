static int verify_clean_subdirectory(const struct cache_entry *ce,
				     enum unpack_trees_error_types error_type,
				     struct unpack_trees_options *o)
{
	/*
	 * we are about to extract "ce->name"; we would not want to lose
	 * anything in the existing directory there.
	 */
	int namelen;
	int i;
	struct dir_struct d;
	char *pathbuf;
	int cnt = 0;

	if (S_ISGITLINK(ce->ce_mode)) {
		unsigned char sha1[20];
		int sub_head = resolve_gitlink_ref(ce->name, "HEAD", sha1);
		/*
		 * If we are not going to update the submodule, then
		 * we don't care.
		 */
		if (!sub_head && !hashcmp(sha1, ce->oid.hash))
			return 0;
		return verify_clean_submodule(sub_head ? NULL : sha1_to_hex(sha1),
					      ce, error_type, o);
	}

	/*
	 * First let's make sure we do not have a local modification
	 * in that directory.
	 */
	namelen = ce_namelen(ce);
	for (i = locate_in_src_index(ce, o);
	     i < o->src_index->cache_nr;
	     i++) {
		struct cache_entry *ce2 = o->src_index->cache[i];
		int len = ce_namelen(ce2);
		if (len < namelen ||
		    strncmp(ce->name, ce2->name, namelen) ||
		    ce2->name[namelen] != '/')
			break;
		/*
		 * ce2->name is an entry in the subdirectory to be
		 * removed.
		 */
		if (!ce_stage(ce2)) {
			if (verify_uptodate(ce2, o))
				return -1;
			add_entry(o, ce2, CE_REMOVE, 0);
			mark_ce_used(ce2, o);
		}
		cnt++;
	}

	/*
	 * Then we need to make sure that we do not lose a locally
	 * present file that is not ignored.
	 */
	pathbuf = xstrfmt("%.*s/", namelen, ce->name);

	memset(&d, 0, sizeof(d));
	if (o->dir)
		d.exclude_per_dir = o->dir->exclude_per_dir;
	i = read_directory(&d, &the_index, pathbuf, namelen+1, NULL);
	if (i)
		return o->gently ? -1 :
			add_rejected_path(o, ERROR_NOT_UPTODATE_DIR, ce->name);
	free(pathbuf);
	return cnt;
}