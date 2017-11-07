static struct stored_bitmap *store_bitmap(struct bitmap_index *index,
					  struct ewah_bitmap *root,
					  const unsigned char *sha1,
					  struct stored_bitmap *xor_with,
					  int flags)
{
	struct stored_bitmap *stored;
	khiter_t hash_pos;
	int ret;

	stored = xmalloc(sizeof(struct stored_bitmap));
	stored->root = root;
	stored->xor = xor_with;
	stored->flags = flags;
	hashcpy(stored->sha1, sha1);

	hash_pos = kh_put_sha1(index->bitmaps, stored->sha1, &ret);

	/* a 0 return code means the insertion succeeded with no changes,
	 * because the SHA1 already existed on the map. this is bad, there
	 * shouldn't be duplicated commits in the index */
	if (ret == 0) {
		error("Duplicate entry in bitmap index: %s", sha1_to_hex(sha1));
		return NULL;
	}

	kh_value(index->bitmaps, hash_pos) = stored;
	return stored;
}