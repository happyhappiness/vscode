	else {
		/* Reading from stdin */
		mode = 0;
		if (strbuf_read(&buf, 0, 0) < 0)
			die_errno("failed to read from stdin");
	}
	convert_to_git(path, buf.buf, buf.len, &buf, 0);
	origin->file.ptr = buf.buf;
	origin->file.size = buf.len;
	pretend_sha1_file(buf.buf, buf.len, OBJ_BLOB, origin->blob_sha1);

	/*
	 * Read the current index, replace the path entry with
