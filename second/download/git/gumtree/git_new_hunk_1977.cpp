	NULL
};

static const char note_template[] =
	"\nWrite/edit the notes for the following object:\n";

struct note_data {
	int given;
	int use_editor;
	char *edit_path;
	struct strbuf buf;
};

static void free_note_data(struct note_data *d)
{
	if (d->edit_path) {
		unlink_or_warn(d->edit_path);
		free(d->edit_path);
	}
	strbuf_release(&d->buf);
}

static int list_each_note(const unsigned char *object_sha1,
		const unsigned char *note_sha1, char *note_path,
		void *cb_data)
{
	printf("%s %s\n", sha1_to_hex(note_sha1), sha1_to_hex(object_sha1));
	return 0;
}

static void copy_obj_to_fd(int fd, const unsigned char *sha1)
{
	unsigned long size;
	enum object_type type;
	char *buf = read_sha1_file(sha1, &type, &size);
	if (buf) {
		if (size)
