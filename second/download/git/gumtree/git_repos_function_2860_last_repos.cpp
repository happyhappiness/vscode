int xmkstemp_mode(char *template, int mode)
{
	int fd;
	char origtemplate[PATH_MAX];
	strlcpy(origtemplate, template, sizeof(origtemplate));

	fd = git_mkstemp_mode(template, mode);
	if (fd < 0) {
		int saved_errno = errno;
		const char *nonrelative_template;

		if (!template[0])
			template = origtemplate;

		nonrelative_template = absolute_path(template);
		errno = saved_errno;
		die_errno("Unable to create temporary file '%s'",
			nonrelative_template);
	}
	return fd;
}