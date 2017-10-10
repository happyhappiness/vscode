		    to_tempfile ? topath[ce_stage(ce)] : NULL) < 0)
			errs++;
	}

	if (did_checkout) {
		if (to_tempfile)
			write_tempfile_record(name, prefix);
		return errs > 0 ? -1 : 0;
	}

	if (!state.quiet) {
		fprintf(stderr, "git checkout-index: %s ", name);
		if (!has_same_name)
