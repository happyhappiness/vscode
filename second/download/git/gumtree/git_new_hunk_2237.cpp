	if (signed_add_overflows(*offset, size))
		die("pack too large for current definition of off_t");
	*offset += size;
	return WRITE_ONE_WRITTEN;
}

static int mark_tagged(const char *path, const struct object_id *oid, int flag,
		       void *cb_data)
{
	unsigned char peeled[20];
	struct object_entry *entry = packlist_find(&to_pack, oid->hash, NULL);

	if (entry)
		entry->tagged = 1;
	if (!peel_ref(path, peeled)) {
		entry = packlist_find(&to_pack, peeled, NULL);
		if (entry)
