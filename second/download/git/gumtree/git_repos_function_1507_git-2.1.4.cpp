static char *sha1_get_pack_name(const unsigned char *sha1,
				char **name, char **base, const char *which)
{
	static const char hex[] = "0123456789abcdef";
	char *buf;
	int i;

	if (!*base) {
		const char *sha1_file_directory = get_object_directory();
		int len = strlen(sha1_file_directory);
		*base = xmalloc(len + 60);
		sprintf(*base, "%s/pack/pack-1234567890123456789012345678901234567890.%s",
			sha1_file_directory, which);
		*name = *base + len + 11;
	}

	buf = *name;

	for (i = 0; i < 20; i++) {
		unsigned int val = *sha1++;
		*buf++ = hex[val >> 4];
		*buf++ = hex[val & 0xf];
	}

	return *base;
}