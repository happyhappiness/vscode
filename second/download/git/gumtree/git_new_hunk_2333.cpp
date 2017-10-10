
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
	if (status < 0)
		; /* Do nothing */
	else if (hdrbuf.len) {
		if ((status = parse_sha1_header_extended(hdrbuf.buf, oi, flags)) < 0)
			status = error("unable to parse %s header with --allow-unknown-type",
				       sha1_to_hex(sha1));
	} else if ((status = parse_sha1_header_extended(hdr, oi, flags)) < 0)
		status = error("unable to parse %s header", sha1_to_hex(sha1));
	git_inflate_end(&stream);
	munmap(map, mapsize);
	if (status && oi->typep)
		*oi->typep = status;
	strbuf_release(&hdrbuf);
	return 0;
}

int sha1_object_info_extended(const unsigned char *sha1, struct object_info *oi, unsigned flags)
{
	struct cached_object *co;
	struct pack_entry e;
	int rtype;
	enum object_type real_type;
	const unsigned char *real = lookup_replace_object_extended(sha1, flags);

	co = find_cached_object(real);
	if (co) {
		if (oi->typep)
			*(oi->typep) = co->type;
		if (oi->sizep)
			*(oi->sizep) = co->size;
		if (oi->disk_sizep)
			*(oi->disk_sizep) = 0;
		if (oi->delta_base_sha1)
			hashclr(oi->delta_base_sha1);
		if (oi->typename)
			strbuf_addstr(oi->typename, typename(co->type));
		oi->whence = OI_CACHED;
		return 0;
	}

	if (!find_pack_entry(real, &e)) {
		/* Most likely it's a loose object. */
		if (!sha1_loose_object_info(real, oi, flags)) {
			oi->whence = OI_LOOSE;
			return 0;
		}

		/* Not a loose object; someone else may have just packed it. */
		reprepare_packed_git();
		if (!find_pack_entry(real, &e))
			return -1;
	}

	/*
	 * packed_object_info() does not follow the delta chain to
	 * find out the real type, unless it is given oi->typep.
	 */
	if (oi->typename && !oi->typep)
		oi->typep = &real_type;

	rtype = packed_object_info(e.p, e.offset, oi);
	if (rtype < 0) {
		mark_bad_packed_object(e.p, real);
		if (oi->typep == &real_type)
			oi->typep = NULL;
		return sha1_object_info_extended(real, oi, 0);
	} else if (in_delta_base_cache(e.p, e.offset)) {
		oi->whence = OI_DBCACHED;
	} else {
		oi->whence = OI_PACKED;
		oi->u.packed.offset = e.offset;
		oi->u.packed.pack = e.p;
		oi->u.packed.is_delta = (rtype == OBJ_REF_DELTA ||
					 rtype == OBJ_OFS_DELTA);
	}
	if (oi->typename)
		strbuf_addstr(oi->typename, typename(*oi->typep));
	if (oi->typep == &real_type)
		oi->typep = NULL;

	return 0;
}

/* returns enum object_type or negative */
int sha1_object_info(const unsigned char *sha1, unsigned long *sizep)
