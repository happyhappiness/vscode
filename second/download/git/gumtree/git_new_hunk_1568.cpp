			    ce_stage(ce), fullname.buf,
			    ce_stage(ce), filename);
	}

	if (file_exists(filename))
		die("Path '%s' exists on disk, but not in the index.", filename);
	if (is_missing_file_error(errno))
		die("Path '%s' does not exist (neither on disk nor in the index).",
		    filename);

	strbuf_release(&fullname);
}

