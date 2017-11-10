static struct entry * convert_entry(unsigned char *sha1)
{
	struct entry *entry = lookup_entry(sha1);
	enum object_type type;
	void *buffer, *data;
	unsigned long size;

	if (entry->converted)
		return entry;
	data = read_sha1_file(sha1, &type, &size);
	if (!data)
		die("unable to read object %s", sha1_to_hex(sha1));

	buffer = xmalloc(size);
	memcpy(buffer, data, size);

	if (type == OBJ_BLOB) {
		write_sha1_file(buffer, size, blob_type, entry->new_sha1);
	} else if (type == OBJ_TREE)
		convert_tree(buffer, size, entry->new_sha1);
	else if (type == OBJ_COMMIT)
		convert_commit(buffer, size, entry->new_sha1);
	else
		die("unknown object type %d in %s", type, sha1_to_hex(sha1));
	entry->converted = 1;
	free(buffer);
	free(data);
	return entry;
}