		find_alignment(sb, &opt);
		output(sb, opt);
		die("Baa %d!", baa);
	}
}

/*
 * Used for the command line parsing; check if the path exists
 * in the working tree.
 */
static int has_string_in_work_tree(const char *path)
{
	struct stat st;
	return !lstat(path, &st);
}

static unsigned parse_score(const char *arg)
{
	char *end;
	unsigned long score = strtoul(arg, &end, 10);
	if (*end)
		return 0;
