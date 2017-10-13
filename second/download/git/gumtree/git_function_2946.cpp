static int add_mailname_host(struct strbuf *buf)
{
	FILE *mailname;
	struct strbuf mailnamebuf = STRBUF_INIT;

	mailname = fopen("/etc/mailname", "r");
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
	}
	/* success! */
	strbuf_addbuf(buf, &mailnamebuf);
	strbuf_release(&mailnamebuf);
	fclose(mailname);
	return 0;
}