static int mark_tagged(const char *path, const unsigned char *sha1, int flag,
		       void *cb_data)
{
	unsigned char peeled[20];
	struct object_entry *entry = packlist_find(&to_pack, sha1, NULL);

	if (entry)
		entry->tagged = 1;
	if (!peel_ref(path, peeled)) {
		entry = packlist_find(&to_pack, peeled, NULL);
		if (entry)
			entry->tagged = 1;
	}
	return 0;
}