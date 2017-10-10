	qsort(entries, nr_objects, sizeof(*entries), compare_entries);

	for (i = 0; i < nr_objects; i++) {
		void *data;
		enum object_type type;
		unsigned long size;

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
		data = unpack_entry(p, entries[i].offset, &type, &size);
		if (!data)
			err = error("cannot unpack %s from %s at offset %"PRIuMAX"",
				    sha1_to_hex(entries[i].sha1), p->pack_name,
				    (uintmax_t)entries[i].offset);
		else if (check_sha1_signature(entries[i].sha1, data, size, typename(type)))
			err = error("packed %s from %s is corrupt",
				    sha1_to_hex(entries[i].sha1), p->pack_name);
