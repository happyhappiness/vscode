	if (!mailname) {
		if (errno != ENOENT)
			warning("cannot open /etc/mailname: %s",
				strerror(errno));
		return -1;
	}
	if (strbuf_getline(&mailnamebuf, mailname) == EOF) {
		if (ferror(mailname))
			warning("cannot read /etc/mailname: %s",
				strerror(errno));
		strbuf_release(&mailnamebuf);
		fclose(mailname);
		return -1;
