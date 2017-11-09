static void init_set_compression(void)
{
	const char *f;
	char *t, *start;

	if (skip_compress)
		add_nocompress_suffixes(skip_compress);

	/* A non-daemon transfer skips the default suffix list if the
	 * user specified --skip-compress. */
	if (skip_compress && module_id < 0)
		f = "";
	else
		f = lp_dont_compress(module_id);

	if (!(match_list = t = new_array(char, strlen(f) + 2)))
		out_of_memory("set_compression");

	per_file_default_level = def_compress_level;

	while (*f) {
		if (*f == ' ') {
			f++;
			continue;
		}

		start = t;
		do {
			if (isUpper(f))
				*t++ = toLower(f);
			else
				*t++ = *f;
		} while (*++f != ' ' && *f);
		*t++ = '\0';

		if (t - start == 1+1 && *start == '*') {
			/* Optimize a match-string of "*". */
			*match_list = '\0';
			suftree = NULL;
			per_file_default_level = 0;
			break;
		}

		/* Move *.foo items into the stuffix tree. */
		if (*start == '*' && start[1] == '.' && start[2]
		 && !strpbrk(start+2, ".?*")) {
			add_suffix(&suftree, start[2], start+3);
			t = start;
		}
	}
	*t++ = '\0';
}