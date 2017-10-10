static int for_each_object_in_pack(struct packed_git *p, each_packed_object_fn cb, void *data)
{
	uint32_t i;
	int r = 0;

	for (i = 0; i < p->num_objects; i++) {
		struct object_id oid;

		if (!nth_packed_object_oid(&oid, p, i))
			return error("unable to get sha1 of object %u in %s",
				     i, p->pack_name);

		r = cb(&oid, p, i, data);
		if (r)
			break;
	}
	return r;
}

