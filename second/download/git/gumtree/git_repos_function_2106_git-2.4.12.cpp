int xmkstemp(char *template)
{
	int fd;
	char origtemplate[PATH_MAX];
	strlcpy(origtemplate, template, sizeof(origtemplate));

	fd = mkstemp(template);
	if (fd < 0) {
		int saved_errno = errno;
		const char *nonrelative_template;

		if (strlen(template) != strlen(origtemplate))
			template = origtemplate;

		nonrelative_template = absolute_path(template);
		errno = saved_errno;
		die_errno("Unable to create temporary file '%s'",
			nonrelative_template);
	}
	return fd;
}