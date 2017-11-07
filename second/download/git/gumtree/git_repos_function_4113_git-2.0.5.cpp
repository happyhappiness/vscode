static int gitdiff_index(const char *line, struct patch *patch)
{
	/*
	 * index line is N hexadecimal, "..", N hexadecimal,
	 * and optional space with octal mode.
	 */
	const char *ptr, *eol;
	int len;

	ptr = strchr(line, '.');
	if (!ptr || ptr[1] != '.' || 40 < ptr - line)
		return 0;
	len = ptr - line;
	memcpy(patch->old_sha1_prefix, line, len);
	patch->old_sha1_prefix[len] = 0;

	line = ptr + 2;
	ptr = strchr(line, ' ');
	eol = strchr(line, '\n');

	if (!ptr || eol < ptr)
		ptr = eol;
	len = ptr - line;

	if (40 < len)
		return 0;
	memcpy(patch->new_sha1_prefix, line, len);
	patch->new_sha1_prefix[len] = 0;
	if (*ptr == ' ')
		patch->old_mode = strtoul(ptr+1, NULL, 8);
	return 0;
}