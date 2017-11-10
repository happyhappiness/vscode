static int
add_to_include_set(struct bitmap *base, struct commit *commit)
{
	khiter_t hash_pos;
	uint32_t bitmap_pos = find_object_pos(commit->object.sha1);

	if (bitmap_get(base, bitmap_pos))
		return 0;

	hash_pos = kh_get_sha1(writer.bitmaps, commit->object.sha1);
	if (hash_pos < kh_end(writer.bitmaps)) {
		struct bitmapped_commit *bc = kh_value(writer.bitmaps, hash_pos);
		bitmap_or_ewah(base, bc->bitmap);
		return 0;
	}

	bitmap_set(base, bitmap_pos);
	return 1;
}