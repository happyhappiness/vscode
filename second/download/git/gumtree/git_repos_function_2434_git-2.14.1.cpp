int ll_merge_marker_size(const char *path)
{
	static struct attr_check *check;
	int marker_size = DEFAULT_CONFLICT_MARKER_SIZE;

	if (!check)
		check = attr_check_initl("conflict-marker-size", NULL);
	if (!git_check_attr(path, check) && check->items[0].value) {
		marker_size = atoi(check->items[0].value);
		if (marker_size <= 0)
			marker_size = DEFAULT_CONFLICT_MARKER_SIZE;
	}
	return marker_size;
}