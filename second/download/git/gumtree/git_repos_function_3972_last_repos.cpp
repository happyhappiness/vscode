static int get_oid_hex_from_objpath(const char *path, struct object_id *oid)
{
	char hex[GIT_MAX_HEXSZ];

	if (strlen(path) != GIT_SHA1_HEXSZ + 1)
		return -1;

	memcpy(hex, path, 2);
	path += 2;
	path++; /* skip '/' */
	memcpy(hex, path, GIT_SHA1_HEXSZ - 2);

	return get_oid_hex(hex, oid);
}