	FILE *stream = fdopen(fd, mode);
	if (stream == NULL)
		die_errno("Out of memory? fdopen failed");
	return stream;
}

FILE *fopen_for_writing(const char *path)
{
	FILE *ret = fopen(path, "w");

	if (!ret && errno == EPERM) {
		if (!unlink(path))
			ret = fopen(path, "w");
		else
			errno = EPERM;
	}
	return ret;
}

int xmkstemp(char *template)
{
	int fd;
	char origtemplate[PATH_MAX];
	strlcpy(origtemplate, template, sizeof(origtemplate));

