
	if (entry->size <= big_file_threshold || entry->type != OBJ_BLOB)
		return -1;

	memset(&data, 0, sizeof(data));
	data.entry = entry;
	data.st = open_istream(entry->idx.sha1, &type, &size, NULL);
	if (!data.st)
		return -1;
	if (size != entry->size || type != entry->type)
		die(_("SHA1 COLLISION FOUND WITH %s !"),
		    sha1_to_hex(entry->idx.sha1));
	unpack_data(entry, compare_objects, &data);
	close_istream(data.st);
	free(data.buf);
	return 0;
}

static void sha1_object(const void *data, struct object_entry *obj_entry,
			unsigned long size, enum object_type type,
			const unsigned char *sha1)
{
	void *new_data = NULL;
	int collision_test_needed = 0;

	assert(data || obj_entry);

	if (startup_info->have_repository) {
		read_lock();
		collision_test_needed = has_sha1_file_with_flags(sha1, HAS_SHA1_QUICK);
		read_unlock();
	}

	if (collision_test_needed && !data) {
		read_lock();
		if (!check_collison(obj_entry))
