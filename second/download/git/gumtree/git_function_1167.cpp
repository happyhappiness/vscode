static int do_write_index(struct index_state *istate, struct tempfile *tempfile,
			  int strip_extensions)
{
	int newfd = tempfile->fd;
	git_SHA_CTX c;
	struct cache_header hdr;
	int i, err, removed, extended, hdr_version;
	struct cache_entry **cache = istate->cache;
	int entries = istate->cache_nr;
	struct stat st;
	struct strbuf previous_name_buf = STRBUF_INIT, *previous_name;

	for (i = removed = extended = 0; i < entries; i++) {
		if (cache[i]->ce_flags & CE_REMOVE)
			removed++;

		/* reduce extended entries if possible */
		cache[i]->ce_flags &= ~CE_EXTENDED;
		if (cache[i]->ce_flags & CE_EXTENDED_FLAGS) {
			extended++;
			cache[i]->ce_flags |= CE_EXTENDED;
		}
	}

	if (!istate->version) {
		istate->version = get_index_format_default();
		if (getenv("GIT_TEST_SPLIT_INDEX"))
			init_split_index(istate);
	}

	/* demote version 3 to version 2 when the latter suffices */
	if (istate->version == 3 || istate->version == 2)
		istate->version = extended ? 3 : 2;

	hdr_version = istate->version;

	hdr.hdr_signature = htonl(CACHE_SIGNATURE);
	hdr.hdr_version = htonl(hdr_version);
	hdr.hdr_entries = htonl(entries - removed);

	git_SHA1_Init(&c);
	if (ce_write(&c, newfd, &hdr, sizeof(hdr)) < 0)
		return -1;

	previous_name = (hdr_version == 4) ? &previous_name_buf : NULL;
	for (i = 0; i < entries; i++) {
		struct cache_entry *ce = cache[i];
		if (ce->ce_flags & CE_REMOVE)
			continue;
		if (!ce_uptodate(ce) && is_racy_timestamp(istate, ce))
			ce_smudge_racily_clean_entry(ce);
		if (is_null_oid(&ce->oid)) {
			static const char msg[] = "cache entry has null sha1: %s";
			static int allow = -1;

			if (allow < 0)
				allow = git_env_bool("GIT_ALLOW_NULL_SHA1", 0);
			if (allow)
				warning(msg, ce->name);
			else
				return error(msg, ce->name);
		}
		if (ce_write_entry(&c, newfd, ce, previous_name) < 0)
			return -1;
	}
	strbuf_release(&previous_name_buf);

	/* Write extension data here */
	if (!strip_extensions && istate->split_index) {
		struct strbuf sb = STRBUF_INIT;

		err = write_link_extension(&sb, istate) < 0 ||
			write_index_ext_header(&c, newfd, CACHE_EXT_LINK,
					       sb.len) < 0 ||
			ce_write(&c, newfd, sb.buf, sb.len) < 0;
		strbuf_release(&sb);
		if (err)
			return -1;
	}
	if (!strip_extensions && istate->cache_tree) {
		struct strbuf sb = STRBUF_INIT;

		cache_tree_write(&sb, istate->cache_tree);
		err = write_index_ext_header(&c, newfd, CACHE_EXT_TREE, sb.len) < 0
			|| ce_write(&c, newfd, sb.buf, sb.len) < 0;
		strbuf_release(&sb);
		if (err)
			return -1;
	}
	if (!strip_extensions && istate->resolve_undo) {
		struct strbuf sb = STRBUF_INIT;

		resolve_undo_write(&sb, istate->resolve_undo);
		err = write_index_ext_header(&c, newfd, CACHE_EXT_RESOLVE_UNDO,
					     sb.len) < 0
			|| ce_write(&c, newfd, sb.buf, sb.len) < 0;
		strbuf_release(&sb);
		if (err)
			return -1;
	}
	if (!strip_extensions && istate->untracked) {
		struct strbuf sb = STRBUF_INIT;

		write_untracked_extension(&sb, istate->untracked);
		err = write_index_ext_header(&c, newfd, CACHE_EXT_UNTRACKED,
					     sb.len) < 0 ||
			ce_write(&c, newfd, sb.buf, sb.len) < 0;
		strbuf_release(&sb);
		if (err)
			return -1;
	}

	if (ce_flush(&c, newfd, istate->sha1))
		return -1;
	if (close_tempfile(tempfile))
		return error(_("could not close '%s'"), tempfile->filename.buf);
	if (stat(tempfile->filename.buf, &st))
		return -1;
	istate->timestamp.sec = (unsigned int)st.st_mtime;
	istate->timestamp.nsec = ST_MTIME_NSEC(st);
	return 0;
}