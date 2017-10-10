
		close(fd);
		strbuf_release(&buf);
		strbuf_reset(&d->buf);

		if (launch_editor(d->edit_path, &d->buf, NULL)) {
			die(_("please supply the note contents using either -m or -F option"));
		}
		strbuf_stripspace(&d->buf, 1);
	}
}

static void write_note_data(struct note_data *d, unsigned char *sha1)
{
	if (write_sha1_file(d->buf.buf, d->buf.len, blob_type, sha1)) {
		error(_("unable to write note object"));
		if (d->edit_path)
			error(_("the note contents have been left in %s"),
				d->edit_path);
		exit(128);
	}
}

static int parse_msg_arg(const struct option *opt, const char *arg, int unset)
