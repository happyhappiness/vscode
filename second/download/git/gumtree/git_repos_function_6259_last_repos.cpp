static int add_object_entry(const unsigned char *sha1, enum object_type type,
			    const char *name, int exclude)
{
	struct packed_git *found_pack = NULL;
	off_t found_offset = 0;
	uint32_t index_pos;

	if (have_duplicate_entry(sha1, exclude, &index_pos))
		return 0;

	if (!want_object_in_pack(sha1, exclude, &found_pack, &found_offset)) {
		/* The pack is missing an object, so it will not have closure */
		if (write_bitmap_index) {
			warning(_(no_closure_warning));
			write_bitmap_index = 0;
		}
		return 0;
	}

	create_object_entry(sha1, type, pack_name_hash(name),
			    exclude, name && no_try_delta(name),
			    index_pos, found_pack, found_offset);

	display_progress(progress_state, nr_result);
	return 1;
}