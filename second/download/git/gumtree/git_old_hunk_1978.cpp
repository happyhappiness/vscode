
	if (finish_command(&show))
		die(_("failed to finish 'show' for object '%s'"),
		    sha1_to_hex(object));
}

static void create_note(const unsigned char *object, struct msg_arg *msg,
			int append_only, const unsigned char *prev,
			unsigned char *result)
{
	char *path = NULL;

	if (msg->use_editor || !msg->given) {
		int fd;
		struct strbuf buf = STRBUF_INIT;

		/* write the template message before editing: */
		path = git_pathdup("NOTES_EDITMSG");
		fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (fd < 0)
			die_errno(_("could not create file '%s'"), path);

		if (msg->given)
			write_or_die(fd, msg->buf.buf, msg->buf.len);
		else if (prev && !append_only)
			write_note_data(fd, prev);

		strbuf_addch(&buf, '\n');
		strbuf_add_commented_lines(&buf, note_template, strlen(note_template));
		strbuf_addch(&buf, '\n');
		write_or_die(fd, buf.buf, buf.len);

		write_commented_object(fd, object);

		close(fd);
		strbuf_release(&buf);
		strbuf_reset(&(msg->buf));

		if (launch_editor(path, &(msg->buf), NULL)) {
			die(_("Please supply the note contents using either -m" \
			    " or -F option"));
		}
		stripspace(&(msg->buf), 1);
	}

	if (prev && append_only) {
		/* Append buf to previous note contents */
		unsigned long size;
		enum object_type type;
		char *prev_buf = read_sha1_file(prev, &type, &size);

		strbuf_grow(&(msg->buf), size + 1);
		if (msg->buf.len && prev_buf && size)
			strbuf_insert(&(msg->buf), 0, "\n", 1);
		if (prev_buf && size)
			strbuf_insert(&(msg->buf), 0, prev_buf, size);
		free(prev_buf);
	}

	if (!msg->buf.len) {
		fprintf(stderr, _("Removing note for object %s\n"),
			sha1_to_hex(object));
		hashclr(result);
	} else {
		if (write_sha1_file(msg->buf.buf, msg->buf.len, blob_type, result)) {
			error(_("unable to write note object"));
			if (path)
				error(_("The note contents have been left in %s"),
				      path);
			exit(128);
		}
	}

	if (path) {
		unlink_or_warn(path);
		free(path);
	}
}

static int parse_msg_arg(const struct option *opt, const char *arg, int unset)
{
	struct msg_arg *msg = opt->value;

	strbuf_grow(&(msg->buf), strlen(arg) + 2);
	if (msg->buf.len)
		strbuf_addch(&(msg->buf), '\n');
	strbuf_addstr(&(msg->buf), arg);
	stripspace(&(msg->buf), 0);

	msg->given = 1;
	return 0;
}

static int parse_file_arg(const struct option *opt, const char *arg, int unset)
{
	struct msg_arg *msg = opt->value;

	if (msg->buf.len)
		strbuf_addch(&(msg->buf), '\n');
	if (!strcmp(arg, "-")) {
		if (strbuf_read(&(msg->buf), 0, 1024) < 0)
			die_errno(_("cannot read '%s'"), arg);
	} else if (strbuf_read_file(&(msg->buf), arg, 1024) < 0)
		die_errno(_("could not open or read '%s'"), arg);
	stripspace(&(msg->buf), 0);

	msg->given = 1;
	return 0;
}

static int parse_reuse_arg(const struct option *opt, const char *arg, int unset)
{
	struct msg_arg *msg = opt->value;
	char *buf;
	unsigned char object[20];
	enum object_type type;
	unsigned long len;

	if (msg->buf.len)
		strbuf_addch(&(msg->buf), '\n');

	if (get_sha1(arg, object))
		die(_("Failed to resolve '%s' as a valid ref."), arg);
	if (!(buf = read_sha1_file(object, &type, &len)) || !len) {
		free(buf);
		die(_("Failed to read object '%s'."), arg);
	}
	if (type != OBJ_BLOB) {
		free(buf);
		die(_("Cannot read note data from non-blob object '%s'."), arg);
	}
	strbuf_add(&(msg->buf), buf, len);
	free(buf);

	msg->given = 1;
	return 0;
}

static int parse_reedit_arg(const struct option *opt, const char *arg, int unset)
{
	struct msg_arg *msg = opt->value;
	msg->use_editor = 1;
	return parse_reuse_arg(opt, arg, unset);
}

static int notes_copy_from_stdin(int force, const char *rewrite_cmd)
{
	struct strbuf buf = STRBUF_INIT;
