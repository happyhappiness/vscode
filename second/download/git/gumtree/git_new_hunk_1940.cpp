	pw = getpwuid(getuid());
	if (!pw)
		die(_("unable to look up current user in the passwd file: %s"),
		    errno ? strerror(errno) : _("no such user"));
	return pw;
}

char *xgetcwd(void)
{
	struct strbuf sb = STRBUF_INIT;
	if (strbuf_getcwd(&sb))
		die_errno(_("unable to get current working directory"));
	return strbuf_detach(&sb, NULL);
}
