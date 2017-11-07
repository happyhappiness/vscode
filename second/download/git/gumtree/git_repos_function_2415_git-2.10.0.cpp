FILE *xfopen(const char *path, const char *mode)
{
	for (;;) {
		FILE *fp = fopen(path, mode);
		if (fp)
			return fp;
		if (errno == EINTR)
			continue;

		if (*mode && mode[1] == '+')
			die_errno(_("could not open '%s' for reading and writing"), path);
		else if (*mode == 'w' || *mode == 'a')
			die_errno(_("could not open '%s' for writing"), path);
		else
			die_errno(_("could not open '%s' for reading"), path);
	}
}