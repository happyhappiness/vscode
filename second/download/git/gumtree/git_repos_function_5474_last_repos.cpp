static void *origin(struct merge_list *entry, unsigned long *size)
{
	enum object_type type;
	while (entry) {
		if (entry->stage == 2)
			return read_sha1_file(entry->blob->object.oid.hash, &type, size);
		entry = entry->link;
	}
	return NULL;
}