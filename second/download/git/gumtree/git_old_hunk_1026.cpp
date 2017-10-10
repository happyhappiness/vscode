
	if (options & BITMAP_OPT_HASH_CACHE)
		write_hash_cache(f, index, index_nr);

	sha1close(f, NULL, CSUM_FSYNC);

	if (adjust_shared_perm(tmp_file))
		die_errno("unable to make temporary bitmap file readable");

	if (rename(tmp_file, filename))
		die_errno("unable to rename temporary bitmap file to '%s'", filename);
}
