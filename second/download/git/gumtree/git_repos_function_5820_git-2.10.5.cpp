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
		strbuf_add_commented_lines(&buf, "\n", strlen("\n"));
		strbuf_add_commented_lines(&buf, _(note_template), strlen(_(note_template)));
		strbuf_addch(&buf, '\n');
		write_or_die(fd, buf.buf, buf.len);

		write_commented_object(fd, object);

		close(fd);
		strbuf_release(&buf);
		strbuf_reset(&d->buf);

		if (launch_editor(d->edit_path, &d->buf, NULL)) {
			die(_("Please supply the note contents using either -m or -F option"));
		}
		strbuf_stripspace(&d->buf, 1);
	}
}