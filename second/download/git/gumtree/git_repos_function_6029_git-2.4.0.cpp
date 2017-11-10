static int write_subdirectory(void *buffer, unsigned long size, const char *base, int baselen, unsigned char *result_sha1)
{
	char *new = xmalloc(size);
	unsigned long newlen = 0;
	unsigned long used;

	used = 0;
	while (size) {
		int len = 21 + strlen(buffer);
		char *path = strchr(buffer, ' ');
		unsigned char *sha1;
		unsigned int mode;
		char *slash, *origpath;

		if (!path || strtoul_ui(buffer, 8, &mode))
			die("bad tree conversion");
		mode = convert_mode(mode);
		path++;
		if (memcmp(path, base, baselen))
			break;
		origpath = path;
		path += baselen;
		slash = strchr(path, '/');
		if (!slash) {
			newlen += sprintf(new + newlen, "%o %s", mode, path);
			new[newlen++] = '\0';
			hashcpy((unsigned char *)new + newlen, (unsigned char *) buffer + len - 20);
			newlen += 20;

			used += len;
			size -= len;
			buffer = (char *) buffer + len;
			continue;
		}

		newlen += sprintf(new + newlen, "%o %.*s", S_IFDIR, (int)(slash - path), path);
		new[newlen++] = 0;
		sha1 = (unsigned char *)(new + newlen);
		newlen += 20;

		len = write_subdirectory(buffer, size, origpath, slash-origpath+1, sha1);

		used += len;
		size -= len;
		buffer = (char *) buffer + len;
	}

	write_sha1_file(new, newlen, tree_type, result_sha1);
	free(new);
	return used;
}