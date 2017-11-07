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