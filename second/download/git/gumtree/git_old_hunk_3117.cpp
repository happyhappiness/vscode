	const char *filename = git_path_bisect_names();
	FILE *fp = fopen(filename, "r");

	if (!fp)
		die_errno("Could not open file '%s'", filename);

	while (strbuf_getline(&str, fp, '\n') != EOF) {
		strbuf_trim(&str);
		if (sq_dequote_to_argv_array(str.buf, array))
			die("Badly quoted content in file '%s': %s",
			    filename, str.buf);
	}

