			if (!sub)
				die("cache-tree.c: '%.*s' in '%s' not found",
				    entlen, path + baselen, path);
			i += sub->count;
			sha1 = sub->cache_tree->sha1;
			mode = S_IFDIR;
			if (sub->cache_tree->entry_count < 0)
				to_invalidate = 1;
		}
		else {
			sha1 = ce->sha1;
			mode = ce->ce_mode;
			entlen = pathlen - baselen;
			i++;
		}
		if (mode != S_IFGITLINK && !missing_ok && !has_sha1_file(sha1)) {
			strbuf_release(&buffer);
			return error("invalid object %06o %s for '%.*s'",
				mode, sha1_to_hex(sha1), entlen+baselen, path);
		}

		/*
		 * CE_REMOVE entries are removed before the index is
