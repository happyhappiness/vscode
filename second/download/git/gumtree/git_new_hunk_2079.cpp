		struct diff_filespec *spec;
		long begin = 0, end = 0;
		long anchor;

		name_part = skip_range_arg(item->string);
		if (!name_part || *name_part != ':' || !name_part[1])
			die("-L argument '%s' not of the form start,end:file",
			    item->string);
		range_part = xstrndup(item->string, name_part - item->string);
		name_part++;

		full_name = prefix_path(prefix, prefix ? strlen(prefix) : 0,
					name_part);
