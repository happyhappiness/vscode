static int prune_object(const unsigned char *sha1, const char *path,
			 void *data)
{
	int *opts = data;

	if (!has_sha1_pack(sha1))
		return 0;

	if (*opts & PRUNE_PACKED_DRY_RUN)
		printf("rm -f %s\n", path);
	else
		unlink_or_warn(path);
	return 0;
}