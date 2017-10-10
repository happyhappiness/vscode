
	offset = entry->in_pack_offset;
	revidx = find_pack_revindex(p, offset);
	datalen = revidx[1].offset - offset;
	if (!pack_to_stdout && p->index_version > 1 &&
	    check_pack_crc(p, &w_curs, offset, datalen, revidx->nr)) {
		error("bad packed object CRC for %s",
		      oid_to_hex(&entry->idx.oid));
		unuse_pack(&w_curs);
		return write_no_reuse_object(f, entry, limit, usable_delta);
	}

	offset += entry->in_pack_header_size;
	datalen -= entry->in_pack_header_size;

	if (!pack_to_stdout && p->index_version == 1 &&
	    check_pack_inflate(p, &w_curs, offset, datalen, entry->size)) {
		error("corrupt packed object for %s",
		      oid_to_hex(&entry->idx.oid));
		unuse_pack(&w_curs);
		return write_no_reuse_object(f, entry, limit, usable_delta);
	}

	if (type == OBJ_OFS_DELTA) {
		off_t ofs = entry->idx.offset - entry->delta->idx.offset;
