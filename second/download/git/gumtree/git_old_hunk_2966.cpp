	int i;

	for (i = 0; i < writer.selected_nr; ++i) {
		struct bitmapped_commit *stored = &writer.selected[i];

		int commit_pos =
			sha1_pos(stored->commit->object.sha1, index, index_nr, sha1_access);

		if (commit_pos < 0)
			die("BUG: trying to write commit not in index");

		sha1write_be32(f, commit_pos);
		sha1write_u8(f, stored->xor_offset);
