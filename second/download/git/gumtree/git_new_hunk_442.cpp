
	/* And add the comment */
	strbuf_add(&buffer, msg, msg_len);

	/* And check the encoding */
	if (encoding_is_utf8 && !verify_utf8(&buffer))
		fprintf(stderr, _(commit_utf8_warn));

	if (sign_commit && do_sign_commit(&buffer, sign_commit))
		return -1;

	result = write_sha1_file(buffer.buf, buffer.len, commit_type, ret);
	strbuf_release(&buffer);
