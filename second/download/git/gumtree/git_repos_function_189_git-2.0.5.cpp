static int load_bitmap_entries_v1(struct bitmap_index *index)
{
	static const size_t MAX_XOR_OFFSET = 160;

	uint32_t i;
	struct stored_bitmap **recent_bitmaps;
	struct bitmap_disk_entry *entry;

	recent_bitmaps = xcalloc(MAX_XOR_OFFSET, sizeof(struct stored_bitmap));

	for (i = 0; i < index->entry_count; ++i) {
		int xor_offset, flags;
		struct ewah_bitmap *bitmap = NULL;
		struct stored_bitmap *xor_bitmap = NULL;
		uint32_t commit_idx_pos;
		const unsigned char *sha1;

		entry = (struct bitmap_disk_entry *)(index->map + index->map_pos);
		index->map_pos += sizeof(struct bitmap_disk_entry);

		commit_idx_pos = ntohl(entry->object_pos);
		sha1 = nth_packed_object_sha1(index->pack, commit_idx_pos);

		xor_offset = (int)entry->xor_offset;
		flags = (int)entry->flags;

		bitmap = read_bitmap_1(index);
		if (!bitmap)
			return -1;

		if (xor_offset > MAX_XOR_OFFSET || xor_offset > i)
			return error("Corrupted bitmap pack index");

		if (xor_offset > 0) {
			xor_bitmap = recent_bitmaps[(i - xor_offset) % MAX_XOR_OFFSET];

			if (xor_bitmap == NULL)
				return error("Invalid XOR offset in bitmap pack index");
		}

		recent_bitmaps[i % MAX_XOR_OFFSET] = store_bitmap(
			index, bitmap, sha1, xor_bitmap, flags);
	}

	return 0;
}