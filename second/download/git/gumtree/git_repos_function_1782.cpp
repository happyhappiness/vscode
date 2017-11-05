static void *read_packed_sha1(const unsigned char *sha1,
			      enum object_type *type, unsigned long *size)
{
	struct pack_entry e;
	void *data;

	if (!find_pack_entry(sha1, &e))
		return NULL;
	data = cache_or_unpack_entry(e.p, e.offset, size, type, 1);
	if (!data) {
		/*
		 * We're probably in deep shit, but let's try to fetch
		 * the required object anyway from another pack or loose.
		 * This should happen only in the presence of a corrupted
		 * pack, and is better than failing outright.
		 */
		error("failed to read object %s at offset %"PRIuMAX" from %s",
		      sha1_to_hex(sha1), (uintmax_t)e.offset, e.p->pack_name);
		mark_bad_packed_object(e.p, sha1);
		data = read_object(sha1, type, size);
	}
	return data;
}