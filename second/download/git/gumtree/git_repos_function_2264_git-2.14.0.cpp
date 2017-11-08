int sha1_object_info_extended(const unsigned char *sha1, struct object_info *oi, unsigned flags)
{
	static struct object_info blank_oi = OBJECT_INFO_INIT;
	struct pack_entry e;
	int rtype;
	const unsigned char *real = (flags & OBJECT_INFO_LOOKUP_REPLACE) ?
				    lookup_replace_object(sha1) :
				    sha1;

	if (!oi)
		oi = &blank_oi;

	if (!(flags & OBJECT_INFO_SKIP_CACHED)) {
		struct cached_object *co = find_cached_object(real);
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
			if (oi->contentp)
				*oi->contentp = xmemdupz(co->buf, co->size);
			oi->whence = OI_CACHED;
			return 0;
		}
	}

	if (!find_pack_entry(real, &e)) {
		/* Most likely it's a loose object. */
		if (!sha1_loose_object_info(real, oi, flags)) {
			oi->whence = OI_LOOSE;
			return 0;
		}

		/* Not a loose object; someone else may have just packed it. */
		if (flags & OBJECT_INFO_QUICK) {
			return -1;
		} else {
			reprepare_packed_git();
			if (!find_pack_entry(real, &e))
				return -1;
		}
	}

	if (oi == &blank_oi)
		/*
		 * We know that the caller doesn't actually need the
		 * information below, so return early.
		 */
		return 0;

	rtype = packed_object_info(e.p, e.offset, oi);
	if (rtype < 0) {
		mark_bad_packed_object(e.p, real);
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

	return 0;
}