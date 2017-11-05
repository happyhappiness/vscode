static uint32_t find_object_pos(const unsigned char *sha1)
{
	struct object_entry *entry = packlist_find(writer.to_pack, sha1, NULL);

	if (!entry) {
		die("Failed to write bitmap index. Packfile doesn't have full closure "
			"(object %s is missing)", sha1_to_hex(sha1));
	}

	return entry->in_pack_pos;
}