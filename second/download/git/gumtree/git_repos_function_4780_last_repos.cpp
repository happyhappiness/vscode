static int path_to_oid(const char *path, struct object_id *oid)
{
	char hex_oid[GIT_SHA1_HEXSZ];
	int i = 0;
	while (*path && i < GIT_SHA1_HEXSZ) {
		if (*path != '/')
			hex_oid[i++] = *path;
		path++;
	}
	if (*path || i != GIT_SHA1_HEXSZ)
		return -1;
	return get_oid_hex(hex_oid, oid);
}