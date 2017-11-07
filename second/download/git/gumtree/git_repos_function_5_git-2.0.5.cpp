int parse_tag(struct tag *item)
{
	enum object_type type;
	void *data;
	unsigned long size;
	int ret;

	if (item->object.parsed)
		return 0;
	data = read_sha1_file(item->object.sha1, &type, &size);
	if (!data)
		return error("Could not read %s",
			     sha1_to_hex(item->object.sha1));
	if (type != OBJ_TAG) {
		free(data);
		return error("Object %s not a tag",
			     sha1_to_hex(item->object.sha1));
	}
	ret = parse_tag_buffer(item, data, size);
	free(data);
	return ret;
}