	qsort(entries, nr_objects, sizeof(*entries), compare_entries);

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
