static unsigned long write_no_reuse_object(struct sha1file *f, struct object_entry *entry,
					   unsigned long limit, int usable_delta)
{
	unsigned long size, datalen;
	unsigned char header[MAX_PACK_OBJECT_HEADER],
		      dheader[MAX_PACK_OBJECT_HEADER];
	unsigned hdrlen;
	enum object_type type;
	void *buf;
	struct git_istream *st = NULL;

	if (!usable_delta) {
		if (entry->type == OBJ_BLOB &&
		    entry->size > big_file_threshold &&
		    (st = open_istream(entry->idx.oid.hash, &type, &size, NULL)) != NULL)
			buf = NULL;
		else {
			buf = read_sha1_file(entry->idx.oid.hash, &type,
					     &size);
			if (!buf)
				die(_("unable to read %s"),
				    oid_to_hex(&entry->idx.oid));
		}
		/*
		 * make sure no cached delta data remains from a
		 * previous attempt before a pack split occurred.
		 */
		FREE_AND_NULL(entry->delta_data);
		entry->z_delta_size = 0;
	} else if (entry->delta_data) {
		size = entry->delta_size;
		buf = entry->delta_data;
		entry->delta_data = NULL;
		type = (allow_ofs_delta && entry->delta->idx.offset) ?
			OBJ_OFS_DELTA : OBJ_REF_DELTA;
	} else {
		buf = get_delta(entry);
		size = entry->delta_size;
		type = (allow_ofs_delta && entry->delta->idx.offset) ?
			OBJ_OFS_DELTA : OBJ_REF_DELTA;
	}

	if (st)	/* large blob case, just assume we don't compress well */
		datalen = size;
	else if (entry->z_delta_size)
		datalen = entry->z_delta_size;
	else
		datalen = do_compress(&buf, size);

	/*
	 * The object header is a byte of 'type' followed by zero or
	 * more bytes of length.
	 */
	hdrlen = encode_in_pack_object_header(header, sizeof(header),
					      type, size);

	if (type == OBJ_OFS_DELTA) {
		/*
		 * Deltas with relative base contain an additional
		 * encoding of the relative offset for the delta
		 * base from this object's position in the pack.
		 */
		off_t ofs = entry->idx.offset - entry->delta->idx.offset;
		unsigned pos = sizeof(dheader) - 1;
		dheader[pos] = ofs & 127;
		while (ofs >>= 7)
			dheader[--pos] = 128 | (--ofs & 127);
		if (limit && hdrlen + sizeof(dheader) - pos + datalen + 20 >= limit) {
			if (st)
				close_istream(st);
			free(buf);
			return 0;
		}
		sha1write(f, header, hdrlen);
		sha1write(f, dheader + pos, sizeof(dheader) - pos);
		hdrlen += sizeof(dheader) - pos;
	} else if (type == OBJ_REF_DELTA) {
		/*
		 * Deltas with a base reference contain
		 * an additional 20 bytes for the base sha1.
		 */
		if (limit && hdrlen + 20 + datalen + 20 >= limit) {
			if (st)
				close_istream(st);
			free(buf);
			return 0;
		}
		sha1write(f, header, hdrlen);
		sha1write(f, entry->delta->idx.oid.hash, 20);
		hdrlen += 20;
	} else {
		if (limit && hdrlen + datalen + 20 >= limit) {
			if (st)
				close_istream(st);
			free(buf);
			return 0;
		}
		sha1write(f, header, hdrlen);
	}
	if (st) {
		datalen = write_large_blob_data(st, f, entry->idx.oid.hash);
		close_istream(st);
	} else {
		sha1write(f, buf, datalen);
		free(buf);
	}

	return hdrlen + datalen;
}