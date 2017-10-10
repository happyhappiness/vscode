
	if (finish_command(&show))
		die(_("failed to finish 'show' for object '%s'"),
		    sha1_to_hex(object));
}

static void prepare_note_data(const unsigned char *object, struct note_data *d,
		const unsigned char *old_note)
{
	if (d->use_editor || !d->given) {
		int fd;
		struct strbuf buf = STRBUF_INIT;

		/* write the template message before editing: */
		d->edit_path = git_pathdup("NOTES_EDITMSG");
		fd = open(d->edit_path, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (fd < 0)
			die_errno(_("could not create file '%s'"), d->edit_path);

		if (d->given)
			write_or_die(fd, d->buf.buf, d->buf.len);
		else if (old_note)
			copy_obj_to_fd(fd, old_note);

		strbuf_addch(&buf, '\n');
		strbuf_add_commented_lines(&buf, note_template, strlen(note_template));
		strbuf_addch(&buf, '\n');
		write_or_die(fd, buf.buf, buf.len);

		write_commented_object(fd, object);

		close(fd);
		strbuf_release(&buf);
		strbuf_reset(&d->buf);

		if (launch_editor(d->edit_path, &d->buf, NULL)) {
			die(_("Please supply the note contents using either -m or -F option"));
		}
		stripspace(&d->buf, 1);
	}
}

static void write_note_data(struct note_data *d, unsigned char *sha1)
{
	if (write_sha1_file(d->buf.buf, d->buf.len, blob_type, sha1)) {
		error(_("unable to write note object"));
		if (d->edit_path)
			error(_("The note contents have been left in %s"),
				d->edit_path);
		exit(128);
	}
}

static int parse_msg_arg(const struct option *opt, const char *arg, int unset)
{
	struct note_data *d = opt->value;

	strbuf_grow(&d->buf, strlen(arg) + 2);
	if (d->buf.len)
		strbuf_addch(&d->buf, '\n');
	strbuf_addstr(&d->buf, arg);
	stripspace(&d->buf, 0);

	d->given = 1;
	return 0;
}

static int parse_file_arg(const struct option *opt, const char *arg, int unset)
{
	struct note_data *d = opt->value;

	if (d->buf.len)
		strbuf_addch(&d->buf, '\n');
	if (!strcmp(arg, "-")) {
		if (strbuf_read(&d->buf, 0, 1024) < 0)
			die_errno(_("cannot read '%s'"), arg);
	} else if (strbuf_read_file(&d->buf, arg, 1024) < 0)
		die_errno(_("could not open or read '%s'"), arg);
	stripspace(&d->buf, 0);

	d->given = 1;
	return 0;
}

static int parse_reuse_arg(const struct option *opt, const char *arg, int unset)
{
	struct note_data *d = opt->value;
	char *buf;
	unsigned char object[20];
	enum object_type type;
	unsigned long len;

	if (d->buf.len)
		strbuf_addch(&d->buf, '\n');

	if (get_sha1(arg, object))
		die(_("Failed to resolve '%s' as a valid ref."), arg);
	if (!(buf = read_sha1_file(object, &type, &len))) {
		free(buf);
		die(_("Failed to read object '%s'."), arg);
	}
	if (type != OBJ_BLOB) {
		free(buf);
		die(_("Cannot read note data from non-blob object '%s'."), arg);
	}
	strbuf_add(&d->buf, buf, len);
	free(buf);

	d->given = 1;
	return 0;
}

static int parse_reedit_arg(const struct option *opt, const char *arg, int unset)
{
	struct note_data *d = opt->value;
	d->use_editor = 1;
	return parse_reuse_arg(opt, arg, unset);
}

static int notes_copy_from_stdin(int force, const char *rewrite_cmd)
{
	struct strbuf buf = STRBUF_INIT;
