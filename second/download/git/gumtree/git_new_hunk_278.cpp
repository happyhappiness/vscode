		return error("%s: cannot add to the index - missing --add option?",
			     path);
	report("add '%s'", path);
	return 0;
}

static void chmod_path(char flip, const char *path)
{
	int pos;
	struct cache_entry *ce;

	pos = cache_name_pos(path, strlen(path));
	if (pos < 0)
		goto fail;
	ce = active_cache[pos];
	if (chmod_cache_entry(ce, flip) < 0)
		goto fail;

	report("chmod %cx '%s'", flip, path);
	return;
 fail:
	die("git update-index: cannot chmod %cx '%s'", flip, path);
}

