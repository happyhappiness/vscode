	int status = 0;
	unsigned long mapsize;
	void *map;
	git_zstream stream;
	char hdr[32];
	struct strbuf hdrbuf = STRBUF_INIT;

	if (oi->delta_base_sha1)
		hashclr(oi->delta_base_sha1);

	/*
	 * If we don't care about type or size, then we don't
	 * need to look inside the object at all. Note that we
	 * do not optimize out the stat call, even if the
	 * caller doesn't care about the disk-size, since our
	 * return value implicitly indicates whether the
	 * object even exists.
	 */
	if (!oi->typep && !oi->typename && !oi->sizep) {
		const char *path;
		struct stat st;
		if (stat_sha1_file(sha1, &st, &path) < 0)
			return -1;
		if (oi->disk_sizep)
			*oi->disk_sizep = st.st_size;
		return 0;
	}

	map = map_sha1_file(sha1, &mapsize);
	if (!map)
		return -1;
	if (oi->disk_sizep)
		*oi->disk_sizep = mapsize;
	if ((flags & LOOKUP_UNKNOWN_OBJECT)) {
		if (unpack_sha1_header_to_strbuf(&stream, map, mapsize, hdr, sizeof(hdr), &hdrbuf) < 0)
			status = error("unable to unpack %s header with --allow-unknown-type",
				       sha1_to_hex(sha1));
	} else if (unpack_sha1_header(&stream, map, mapsize, hdr, sizeof(hdr)) < 0)
		status = error("unable to unpack %s header",
			       sha1_to_hex(sha1));
