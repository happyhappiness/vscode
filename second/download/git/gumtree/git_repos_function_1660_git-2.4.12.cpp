static int sha1_loose_object_info(const unsigned char *sha1,
				  struct object_info *oi)
{
	int status;
	unsigned long mapsize, size;
	void *map;
	git_zstream stream;
	char hdr[32];

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
	if (!oi->typep && !oi->sizep) {
		struct stat st;
		if (stat_sha1_file(sha1, &st) < 0)
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
	if (unpack_sha1_header(&stream, map, mapsize, hdr, sizeof(hdr)) < 0)
		status = error("unable to unpack %s header",
			       sha1_to_hex(sha1));
	else if ((status = parse_sha1_header(hdr, &size)) < 0)
		status = error("unable to parse %s header", sha1_to_hex(sha1));
	else if (oi->sizep)
		*oi->sizep = size;
	git_inflate_end(&stream);
	munmap(map, mapsize);
	if (oi->typep)
		*oi->typep = status;
	return 0;
}