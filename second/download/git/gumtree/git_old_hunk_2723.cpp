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
