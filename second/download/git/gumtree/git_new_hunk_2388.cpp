			    "Did you mean ':%d:%s' aka ':%d:./%s'?",
			    fullname, filename,
			    ce_stage(ce), fullname,
			    ce_stage(ce), filename);
	}

	if (file_exists(filename))
		die("Path '%s' exists on disk, but not in the index.", filename);
	if (errno == ENOENT || errno == ENOTDIR)
		die("Path '%s' does not exist (neither on disk nor in the index).",
		    filename);

	free(fullname);
