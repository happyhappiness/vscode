	char *end;
	long nr = strtol(nr_arg, &end, 10);
	long remaining = nr;
	const char *start = refname;

	if (nr < 1 || *end != '\0')
		die(":strip= requires a positive integer argument");

	while (remaining) {
		switch (*start++) {
		case '\0':
			die("ref '%s' does not have %ld components to :strip",
			    refname, nr);
		case '/':
			remaining--;
			break;
		}
	}
	return start;
}

/*
 * Parse the object referred by ref, and grab needed value.
 */
static void populate_value(struct ref_array_item *ref)
{
	void *buf;
