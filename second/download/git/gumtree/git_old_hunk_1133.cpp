		error_errno("cannot open mbox %s", file);
		goto out;
	}

	do {
		peek = fgetc(f);
	} while (isspace(peek));
	ungetc(peek, f);

	if (strbuf_getwholeline(&buf, f, '\n')) {
		/* empty stdin is OK */
		if (f != stdin) {
