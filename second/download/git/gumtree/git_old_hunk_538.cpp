	char *buf = xstrdup(path);
	enum scld_error result = safe_create_leading_directories(buf);
	free(buf);
	return result;
}

static void fill_sha1_path(char *pathbuf, const unsigned char *sha1)
{
	int i;
	for (i = 0; i < 20; i++) {
		static char hex[] = "0123456789abcdef";
		unsigned int val = sha1[i];
		char *pos = pathbuf + i*2 + (i > 0);
		*pos++ = hex[val >> 4];
		*pos = hex[val & 0xf];
	}
}

const char *sha1_file_name(const unsigned char *sha1)
{
	static char buf[PATH_MAX];
	const char *objdir;
	int len;

	objdir = get_object_directory();
	len = strlen(objdir);

	/* '/' + sha1(2) + '/' + sha1(38) + '\0' */
	if (len + 43 > PATH_MAX)
		die("insanely long object directory %s", objdir);
	memcpy(buf, objdir, len);
	buf[len] = '/';
	buf[len+3] = '/';
	buf[len+42] = '\0';
	fill_sha1_path(buf + len + 1, sha1);
	return buf;
}

/*
 * Return the name of the pack or index file with the specified sha1
 * in its filename.  *base and *name are scratch space that must be
 * provided by the caller.  which should be "pack" or "idx".
