static void *result(struct merge_list *entry, unsigned long *size)
{
	enum object_type type;
	struct blob *base, *our, *their;
	const char *path = entry->path;

	if (!entry->stage)
		return read_sha1_file(entry->blob->object.oid.hash, &type, size);
	base = NULL;
	if (entry->stage == 1) {
		base = entry->blob;
		entry = entry->link;
	}
	our = NULL;
	if (entry && entry->stage == 2) {
		our = entry->blob;
		entry = entry->link;
	}
	their = NULL;
	if (entry)
		their = entry->blob;
	return merge_blobs(path, base, our, their, size);
}