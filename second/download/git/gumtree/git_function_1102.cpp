const char *write_idx_file(const char *index_name, struct pack_idx_entry **objects,
			   int nr_objects, const struct pack_idx_option *opts,
			   const unsigned char *sha1)
{
	struct sha1file *f;
	struct pack_idx_entry **sorted_by_sha, **list, **last;
	off_t last_obj_offset = 0;
	uint32_t array[256];
	int i, fd;
	uint32_t index_version;

	if (nr_objects) {
		sorted_by_sha = objects;
		list = sorted_by_sha;
		last = sorted_by_sha + nr_objects;
		for (i = 0; i < nr_objects; ++i) {
			if (objects[i]->offset > last_obj_offset)
				last_obj_offset = objects[i]->offset;
		}
		QSORT(sorted_by_sha, nr_objects, sha1_compare);
	}
	else
		sorted_by_sha = list = last = NULL;

	if (opts->flags & WRITE_IDX_VERIFY) {
		assert(index_name);
		f = sha1fd_check(index_name);
	} else {
		if (!index_name) {
			struct strbuf tmp_file = STRBUF_INIT;
			fd = odb_mkstemp(&tmp_file, "pack/tmp_idx_XXXXXX");
			index_name = strbuf_detach(&tmp_file, NULL);
		} else {
			unlink(index_name);
			fd = open(index_name, O_CREAT|O_EXCL|O_WRONLY, 0600);
			if (fd < 0)
				die_errno("unable to create '%s'", index_name);
		}
		f = sha1fd(fd, index_name);
	}

	/* if last object's offset is >= 2^31 we should use index V2 */
	index_version = need_large_offset(last_obj_offset, opts) ? 2 : opts->version;

	/* index versions 2 and above need a header */
	if (index_version >= 2) {
		struct pack_idx_header hdr;
		hdr.idx_signature = htonl(PACK_IDX_SIGNATURE);
		hdr.idx_version = htonl(index_version);
		sha1write(f, &hdr, sizeof(hdr));
	}

	/*
	 * Write the first-level table (the list is sorted,
	 * but we use a 256-entry lookup to be able to avoid
	 * having to do eight extra binary search iterations).
	 */
	for (i = 0; i < 256; i++) {
		struct pack_idx_entry **next = list;
		while (next < last) {
			struct pack_idx_entry *obj = *next;
			if (obj->sha1[0] != i)
				break;
			next++;
		}
		array[i] = htonl(next - sorted_by_sha);
		list = next;
	}
	sha1write(f, array, 256 * 4);

	/*
	 * Write the actual SHA1 entries..
	 */
	list = sorted_by_sha;
	for (i = 0; i < nr_objects; i++) {
		struct pack_idx_entry *obj = *list++;
		if (index_version < 2) {
			uint32_t offset = htonl(obj->offset);
			sha1write(f, &offset, 4);
		}
		sha1write(f, obj->sha1, 20);
		if ((opts->flags & WRITE_IDX_STRICT) &&
		    (i && !hashcmp(list[-2]->sha1, obj->sha1)))
			die("The same object %s appears twice in the pack",
			    sha1_to_hex(obj->sha1));
	}

	if (index_version >= 2) {
		unsigned int nr_large_offset = 0;

		/* write the crc32 table */
		list = sorted_by_sha;
		for (i = 0; i < nr_objects; i++) {
			struct pack_idx_entry *obj = *list++;
			uint32_t crc32_val = htonl(obj->crc32);
			sha1write(f, &crc32_val, 4);
		}

		/* write the 32-bit offset table */
		list = sorted_by_sha;
		for (i = 0; i < nr_objects; i++) {
			struct pack_idx_entry *obj = *list++;
			uint32_t offset;

			offset = (need_large_offset(obj->offset, opts)
				  ? (0x80000000 | nr_large_offset++)
				  : obj->offset);
			offset = htonl(offset);
			sha1write(f, &offset, 4);
		}

		/* write the large offset table */
		list = sorted_by_sha;
		while (nr_large_offset) {
			struct pack_idx_entry *obj = *list++;
			uint64_t offset = obj->offset;
			uint32_t split[2];

			if (!need_large_offset(offset, opts))
				continue;
			split[0] = htonl(offset >> 32);
			split[1] = htonl(offset & 0xffffffff);
			sha1write(f, split, 8);
			nr_large_offset--;
		}
	}

	sha1write(f, sha1, 20);
	sha1close(f, NULL, ((opts->flags & WRITE_IDX_VERIFY)
			    ? CSUM_CLOSE : CSUM_FSYNC));
	return index_name;
}