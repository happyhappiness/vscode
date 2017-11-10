static int path_to_sha1(const char *path, unsigned char *sha1)
{
	char hex_sha1[40];
	int i = 0;
	while (*path && i < 40) {
		if (*path != '/')
			hex_sha1[i++] = *path;
		path++;
	}
	if (*path || i != 40)
		return -1;
	return get_sha1_hex(hex_sha1, sha1);
}