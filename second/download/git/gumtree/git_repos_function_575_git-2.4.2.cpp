void git_setup_gettext(void)
{
	const char *podir = getenv("GIT_TEXTDOMAINDIR");

	if (!podir)
		podir = GIT_LOCALE_PATH;
	bindtextdomain("git", podir);
	setlocale(LC_MESSAGES, "");
	init_gettext_charset("git");
	textdomain("git");
}