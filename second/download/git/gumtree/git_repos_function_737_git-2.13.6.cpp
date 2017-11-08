static int register_replace_object(struct replace_object *replace,
				   int ignore_dups)
{
	int pos = replace_object_pos(replace->original);

	if (0 <= pos) {
		if (ignore_dups)
			free(replace);
		else {
			free(replace_object[pos]);
			replace_object[pos] = replace;
		}
		return 1;
	}
	pos = -pos - 1;
	ALLOC_GROW(replace_object, replace_object_nr + 1, replace_object_alloc);
	replace_object_nr++;
	if (pos < replace_object_nr)
		memmove(replace_object + pos + 1,
			replace_object + pos,
			(replace_object_nr - pos - 1) *
			sizeof(*replace_object));
	replace_object[pos] = replace;
	return 0;
}