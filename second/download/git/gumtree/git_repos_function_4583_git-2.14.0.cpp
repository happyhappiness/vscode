static int add_mailname_host(struct strbuf *buf)
{
	FILE *mailname;
	struct strbuf mailnamebuf = STRBUF_INIT;

	mailname = fopen_or_warn("/etc/mailname", "r");
	if (!mailname)
		return -1;

	if (strbuf_getline(&mailnamebuf, mailname) == EOF) {
		if (ferror(mailname))
			warning_errno("cannot read /etc/mailname");
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