static int find_patch_start(const char *str)
{
	const char *s;

	for (s = str; *s; s = next_line(s)) {
		if (starts_with(s, "---"))
			return s - str;
	}

	return s - str;
}