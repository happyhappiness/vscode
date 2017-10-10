 * for failure.
 */
static int merge(const struct rerere_id *id, const char *path)
{
	FILE *f;
	int ret;
	mmfile_t cur = {NULL, 0};
	mmbuffer_t result = {NULL, 0};

	/*
	 * Normalize the conflicts in path and write it out to
	 * "thisimage" temporary file.
	 */
	if ((handle_file(path, NULL, rerere_path(id, "thisimage")) < 0) ||
	    read_mmfile(&cur, rerere_path(id, "thisimage"))) {
		ret = 1;
		goto out;
	}

	ret = try_merge(id, path, &cur, &result);
	if (ret)
		goto out;

	/*
	 * A successful replay of recorded resolution.
	 * Mark that "postimage" was used to help gc.
	 */
	if (utime(rerere_path(id, "postimage"), NULL) < 0)
		warning_errno("failed utime() on %s",
			      rerere_path(id, "postimage"));

	/* Update "path" with the resolution */
	f = fopen(path, "w");
	if (!f)
		return error_errno("Could not open %s", path);
	if (fwrite(result.ptr, result.size, 1, f) != 1)
		error_errno("Could not write %s", path);
	if (fclose(f))
		return error_errno("Writing %s failed", path);

out:
	free(cur.ptr);
	free(result.ptr);

	return ret;
}

static struct lock_file index_lock;
