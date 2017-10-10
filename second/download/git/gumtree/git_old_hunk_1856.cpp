	 * The first thing we expect from index-pack's output
	 * is "pack\t%40s\n" or "keep\t%40s\n" (46 bytes) where
	 * %40s is the newly created pack SHA1 name.  In the "keep"
	 * case, we need it to remove the corresponding .keep file
	 * later on.  If we don't get that then tough luck with it.
	 */
	if (read_in_full(ip_out, packname, 46) == 46 && packname[45] == '\n' &&
	    memcmp(packname, "keep\t", 5) == 0) {
		char path[PATH_MAX];
		packname[45] = 0;
		snprintf(path, sizeof(path), "%s/pack/pack-%s.keep",
			 get_object_directory(), packname + 5);
		return xstrdup(path);
	}
	return NULL;
}

/*
 * The per-object header is a pretty dense thing, which is
