int parse_oid_hex(const char *hex, struct object_id *oid, const char **end)
{
	int ret = get_oid_hex(hex, oid);
	if (!ret)
		*end = hex + GIT_SHA1_HEXSZ;
	return ret;
}