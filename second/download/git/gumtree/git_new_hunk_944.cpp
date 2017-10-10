	display_progress(progress, nr + 1);
	if (!(*opts & PRUNE_PACKED_DRY_RUN))
		rmdir(path);
	return 0;
}

static int prune_object(const struct object_id *oid, const char *path,
			 void *data)
{
	int *opts = data;

	if (!has_sha1_pack(oid->hash))
		return 0;

	if (*opts & PRUNE_PACKED_DRY_RUN)
		printf("rm -f %s\n", path);
	else
		unlink_or_warn(path);
