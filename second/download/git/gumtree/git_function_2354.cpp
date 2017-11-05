static int merge(const struct rerere_id *id, const char *path)
{
	FILE *f;
	int ret;
	mmfile_t cur = {NULL, 0}, base = {NULL, 0}, other = {NULL, 0};
	mmbuffer_t result = {NULL, 0};

	/*
	 * Normalize the conflicts in path and write it out to
	 * "thisimage" temporary file.
	 */
	if (handle_file(path, NULL, rerere_path(id, "thisimage")) < 0) {
		ret = 1;
		goto out;
	}

	if (read_mmfile(&cur, rerere_path(id, "thisimage")) ||
	    read_mmfile(&base, rerere_path(id, "preimage")) ||
	    read_mmfile(&other, rerere_path(id, "postimage"))) {
		ret = 1;
		goto out;
	}

	/*
	 * A three-way merge. Note that this honors user-customizable
	 * low-level merge driver settings.
	 */
	ret = ll_merge(&result, path, &base, NULL, &cur, "", &other, "", NULL);
	if (ret)
		goto out;

	/*
	 * A successful replay of recorded resolution.
	 * Mark that "postimage" was used to help gc.
	 */
	if (utime(rerere_path(id, "postimage"), NULL) < 0)
		warning("failed utime() on %s: %s",
			rerere_path(id, "postimage"),
			strerror(errno));

	/* Update "path" with the resolution */
	f = fopen(path, "w");
	if (!f)
		return error("Could not open %s: %s", path,
			     strerror(errno));
	if (fwrite(result.ptr, result.size, 1, f) != 1)
		error("Could not write %s: %s", path, strerror(errno));
	if (fclose(f))
		return error("Writing %s failed: %s", path,
			     strerror(errno));

out:
	free(cur.ptr);
	free(base.ptr);
	free(other.ptr);
	free(result.ptr);

	return ret;
}