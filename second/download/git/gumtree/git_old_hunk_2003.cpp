				      uint32_t index_nr)
{
	int i;

	for (i = 0; i < writer.selected_nr; ++i) {
		struct bitmapped_commit *stored = &writer.selected[i];
		struct bitmap_disk_entry on_disk;

		int commit_pos =
			sha1_pos(stored->commit->object.sha1, index, index_nr, sha1_access);

		if (commit_pos < 0)
			die("BUG: trying to write commit not in index");

		on_disk.object_pos = htonl(commit_pos);
		on_disk.xor_offset = stored->xor_offset;
		on_disk.flags = stored->flags;

		sha1write(f, &on_disk, sizeof(on_disk));
		dump_bitmap(f, stored->write_as);
	}
}

static void write_hash_cache(struct sha1file *f,
			     struct pack_idx_entry **index,
