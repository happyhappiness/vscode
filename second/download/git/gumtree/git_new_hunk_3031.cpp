	void *data;
	unsigned long size;
	int ret;

	if (item->object.parsed)
		return 0;
	data = read_sha1_file(item->object.oid.hash, &type, &size);
	if (!data)
		return error("Could not read %s",
			     oid_to_hex(&item->object.oid));
	if (type != OBJ_TAG) {
		free(data);
		return error("Object %s not a tag",
			     oid_to_hex(&item->object.oid));
	}
	ret = parse_tag_buffer(item, data, size);
	free(data);
	return ret;
}
