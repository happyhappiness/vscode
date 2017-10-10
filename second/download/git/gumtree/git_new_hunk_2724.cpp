		strbuf_addch(&d->buf, '\n');
	if (!strcmp(arg, "-")) {
		if (strbuf_read(&d->buf, 0, 1024) < 0)
			die_errno(_("cannot read '%s'"), arg);
	} else if (strbuf_read_file(&d->buf, arg, 1024) < 0)
		die_errno(_("could not open or read '%s'"), arg);
	strbuf_stripspace(&d->buf, 0);

	d->given = 1;
	return 0;
}

static int parse_reuse_arg(const struct option *opt, const char *arg, int unset)
