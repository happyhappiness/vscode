static void write_note_to_worktree(const unsigned char *obj,
				   const unsigned char *note)
{
	enum object_type type;
	unsigned long size;
	void *buf = read_sha1_file(note, &type, &size);

	if (!buf)
		die("cannot read note %s for object %s",
		    sha1_to_hex(note), sha1_to_hex(obj));
	if (type != OBJ_BLOB)
		die("blob expected in note %s for object %s",
		    sha1_to_hex(note), sha1_to_hex(obj));
	write_buf_to_worktree(obj, buf, size);
	free(buf);
}