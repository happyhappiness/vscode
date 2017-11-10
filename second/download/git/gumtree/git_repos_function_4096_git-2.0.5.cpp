static int guess_p_value(const char *nameline)
{
	char *name, *cp;
	int val = -1;

	if (is_dev_null(nameline))
		return -1;
	name = find_name_traditional(nameline, NULL, 0);
	if (!name)
		return -1;
	cp = strchr(name, '/');
	if (!cp)
		val = 0;
	else if (prefix) {
		/*
		 * Does it begin with "a/$our-prefix" and such?  Then this is
		 * very likely to apply to our directory.
		 */
		if (!strncmp(name, prefix, prefix_length))
			val = count_slashes(prefix);
		else {
			cp++;
			if (!strncmp(cp, prefix, prefix_length))
				val = count_slashes(prefix) + 1;
		}
	}
	free(name);
	return val;
}