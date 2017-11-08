static int for_each_object_in_pack(struct packed_git *p, each_packed_object_fn cb, void *data)
{
	uint32_t i;
	int r = 0;

	for (i = 0; i < p->num_objects; i++) {
		const unsigned char *sha1 = nth_packed_object_sha1(p, i);

		if (!sha1)
			return error("unable to get sha1 of object %u in %s",
				     i, p->pack_name);

		r = cb(sha1, p, i, data);
		if (r)
			break;
	}
	return r;
}