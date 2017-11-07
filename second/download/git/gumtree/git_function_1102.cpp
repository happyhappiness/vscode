static int verify_packfile(struct packed_git *p,
			   struct pack_window **w_curs,
			   verify_fn fn,
			   struct progress *progress, uint32_t base_count)

{
	off_t index_size = p->index_size;
	const unsigned char *index_base = p->index_data;
	git_SHA_CTX ctx;
	unsigned char sha1[20], *pack_sig;
	off_t offset = 0, pack_sig_ofs = 0;
	uint32_t nr_objects, i;
	int err = 0;
	struct idx_entry *entries;

	if (!is_pack_valid(p))
		return error("packfile %s cannot be accessed", p->pack_name);

	git_SHA1_Init(&ctx);
	do {
		unsigned long remaining;
		unsigned char *in = use_pack(p, w_curs, offset, &remaining);
		offset += remaining;
		if (!pack_sig_ofs)
			pack_sig_ofs = p->pack_size - 20;
		if (offset > pack_sig_ofs)
			remaining -= (unsigned int)(offset - pack_sig_ofs);
		git_SHA1_Update(&ctx, in, remaining);
	} while (offset < pack_sig_ofs);
	git_SHA1_Final(sha1, &ctx);
	pack_sig = use_pack(p, w_curs, pack_sig_ofs, NULL);
	if (hashcmp(sha1, pack_sig))
		err = error("%s SHA1 checksum mismatch",
			    p->pack_name);
	if (hashcmp(index_base + index_size - 40, pack_sig))
		err = error("%s SHA1 does not match its index",
			    p->pack_name);
	unuse_pack(w_curs);

	/* Make sure everything reachable from idx is valid.  Since we
	 * have verified that nr_objects matches between idx and pack,
	 * we do not do scan-streaming check on the pack file.
	 */
	nr_objects = p->num_objects;
	ALLOC_ARRAY(entries, nr_objects + 1);
	entries[nr_objects].offset = pack_sig_ofs;
	/* first sort entries by pack offset, since unpacking them is more efficient that way */
	for (i = 0; i < nr_objects; i++) {
		entries[i].sha1 = nth_packed_object_sha1(p, i);
		if (!entries[i].sha1)
			die("internal error pack-check nth-packed-object");
		entries[i].offset = nth_packed_object_offset(p, i);
		entries[i].nr = i;
	}
	QSORT(entries, nr_objects, compare_entries);

	for (i = 0; i < nr_objects; i++) {
		void *data;
		enum object_type type;
		unsigned long size;
		off_t curpos;
		int data_valid;

		if (p->index_version > 1) {
			off_t offset = entries[i].offset;
			off_t len = entries[i+1].offset - offset;
			unsigned int nr = entries[i].nr;
			if (check_pack_crc(p, w_curs, offset, len, nr))
				err = error("index CRC mismatch for object %s "
					    "from %s at offset %"PRIuMAX"",
					    sha1_to_hex(entries[i].sha1),
					    p->pack_name, (uintmax_t)offset);
		}

		curpos = entries[i].offset;
		type = unpack_object_header(p, w_curs, &curpos, &size);
		unuse_pack(w_curs);

		if (type == OBJ_BLOB && big_file_threshold <= size) {
			/*
			 * Let check_sha1_signature() check it with
			 * the streaming interface; no point slurping
			 * the data in-core only to discard.
			 */
			data = NULL;
			data_valid = 0;
		} else {
			data = unpack_entry(p, entries[i].offset, &type, &size);
			data_valid = 1;
		}

		if (data_valid && !data)
			err = error("cannot unpack %s from %s at offset %"PRIuMAX"",
				    sha1_to_hex(entries[i].sha1), p->pack_name,
				    (uintmax_t)entries[i].offset);
		else if (check_sha1_signature(entries[i].sha1, data, size, typename(type)))
			err = error("packed %s from %s is corrupt",
				    sha1_to_hex(entries[i].sha1), p->pack_name);
		else if (fn) {
			int eaten = 0;
			err |= fn(entries[i].sha1, type, size, data, &eaten);
			if (eaten)
				data = NULL;
		}
		if (((base_count + i) & 1023) == 0)
			display_progress(progress, base_count + i);
		free(data);

	}
	display_progress(progress, base_count + i);
	free(entries);

	return err;
}