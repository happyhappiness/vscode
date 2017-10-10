		if (conflict_type == PUNTED)
			string_list_insert(merge_rr, (const char *)e->name);
		else if (conflict_type == RESOLVED) {
			struct string_list_item *it;
			it = string_list_lookup(merge_rr, (const char *)e->name);
			if (it != NULL) {
				free(it->util);
				it->util = RERERE_RESOLVED;
			}
		}
	}
	return 0;
}

static int merge(const char *name, const char *path)
{
	int ret;
	mmfile_t cur = {NULL, 0}, base = {NULL, 0}, other = {NULL, 0};
	mmbuffer_t result = {NULL, 0};

	if (handle_file(path, NULL, rerere_path(name, "thisimage")) < 0)
		return 1;

	if (read_mmfile(&cur, rerere_path(name, "thisimage")) ||
			read_mmfile(&base, rerere_path(name, "preimage")) ||
			read_mmfile(&other, rerere_path(name, "postimage"))) {
		ret = 1;
		goto out;
	}
	ret = ll_merge(&result, path, &base, NULL, &cur, "", &other, "", NULL);
	if (!ret) {
		FILE *f;

		if (utime(rerere_path(name, "postimage"), NULL) < 0)
			warning("failed utime() on %s: %s",
					rerere_path(name, "postimage"),
					strerror(errno));
		f = fopen(path, "w");
		if (!f)
			return error("Could not open %s: %s", path,
				     strerror(errno));
		if (fwrite(result.ptr, result.size, 1, f) != 1)
			error("Could not write %s: %s", path, strerror(errno));
		if (fclose(f))
			return error("Writing %s failed: %s", path,
				     strerror(errno));
	}

out:
	free(cur.ptr);
	free(base.ptr);
	free(other.ptr);
	free(result.ptr);
