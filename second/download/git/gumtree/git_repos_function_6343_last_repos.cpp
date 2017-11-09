static int list_each_note(const struct object_id *object_oid,
		const struct object_id *note_oid, char *note_path,
		void *cb_data)
{
	printf("%s %s\n", oid_to_hex(note_oid), oid_to_hex(object_oid));
	return 0;
}