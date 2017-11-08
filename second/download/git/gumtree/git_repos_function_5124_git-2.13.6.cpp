static void unpack_one(unsigned nr)
{
	unsigned shift;
	unsigned char *pack;
	unsigned long size, c;
	enum object_type type;

	obj_list[nr].offset = consumed_bytes;

	pack = fill(1);
	c = *pack;
	use(1);
	type = (c >> 4) & 7;
	size = (c & 15);
	shift = 4;
	while (c & 0x80) {
		pack = fill(1);
		c = *pack;
		use(1);
		size += (c & 0x7f) << shift;
		shift += 7;
	}

	switch (type) {
	case OBJ_COMMIT:
	case OBJ_TREE:
	case OBJ_BLOB:
	case OBJ_TAG:
		unpack_non_delta_entry(type, size, nr);
		return;
	case OBJ_REF_DELTA:
	case OBJ_OFS_DELTA:
		unpack_delta_entry(type, size, nr);
		return;
	default:
		error("bad object type %d", type);
		has_errors = 1;
		if (recover)
			return;
		exit(1);
	}
}