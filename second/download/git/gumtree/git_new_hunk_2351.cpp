		die(_("Could not open '%s' for writing."), file);
	rev.diffopt.file = xfdopen(out, "w");
	rev.diffopt.close_file = 1;
	if (run_diff_files(&rev, 0))
		die(_("Could not write patch"));

	if (launch_editor(file, NULL, NULL))
		die(_("editing patch failed"));

	if (stat(file, &st))
		die_errno(_("Could not stat '%s'"), file);
	if (!st.st_size)
		die(_("Empty patch. Aborted."));

