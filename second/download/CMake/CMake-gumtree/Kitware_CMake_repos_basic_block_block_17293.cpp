{
		int rc;

		/* never write more bytes than announced */
		if (len > w->populz) {
			len = (size_t)w->populz;
		}

		/* now then, out we put the whole shebang */
		rc = __archive_write_output(a, buf, len);
		if (rc != ARCHIVE_OK) {
			return rc;
		}
	}