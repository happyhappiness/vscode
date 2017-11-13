struct passwd *xgetpwuid_self(void)
{
	struct passwd *pw;

	errno = 0;
	pw = getpwuid(getuid());
	if (!pw)
		die(_("unable to look up current user in the passwd file: %s"),
		    errno ? strerror(errno) : _("no such user"));
	return pw;
}