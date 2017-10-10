			sha1_to_hex(object));
		hashclr(result);
	} else {
		if (write_sha1_file(msg->buf.buf, msg->buf.len, blob_type, result)) {
			error(_("unable to write note object"));
			if (path)
				error(_("The note contents has been left in %s"),
				      path);
			exit(128);
		}
	}

	if (path) {
