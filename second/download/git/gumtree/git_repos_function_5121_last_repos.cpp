static int subpath_matches(const char *path, const char *filter)
{
	const char *subpath = path;

	while (subpath) {
		if (!wildmatch(filter, subpath, 0))
			return subpath - path;
		subpath = strchr(subpath, '/');
		if (subpath)
			subpath++;
	}
	return -1;
}