			die("bad revision '%s'", arg);
		as_is = 1;
		if (!show_file(arg, output_prefix))
			continue;
		verify_filename(prefix, arg, 1);
	}
	if (verify) {
		if (revs_count == 1) {
			show_rev(type, sha1, name);
			return 0;
		} else if (revs_count == 0 && show_default())
			return 0;
