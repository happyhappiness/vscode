static int string_list_add_note_lines(struct string_list *list,
				      const unsigned char *sha1)
{
	char *data;
	unsigned long len;
	enum object_type t;

	if (is_null_sha1(sha1))
		return 0;

	/* read_sha1_file NUL-terminates */
	data = read_sha1_file(sha1, &t, &len);
	if (t != OBJ_BLOB || !data || !len) {
		free(data);
		return t != OBJ_BLOB || !data;
	}

	/*
	 * If the last line of the file is EOL-terminated, this will
	 * add an empty string to the list.  But it will be removed
	 * later, along with any empty strings that came from empty
	 * lines within the file.
	 */
	string_list_split(list, data, '\n', -1);
	free(data);
	return 0;
}