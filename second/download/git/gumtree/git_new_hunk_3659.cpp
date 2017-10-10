	if (!use_stdout)
		output_directory = set_outdir(prefix, output_directory);
	else
		setup_pager();

	if (output_directory) {
		if (rev.diffopt.use_color != GIT_COLOR_ALWAYS)
			rev.diffopt.use_color = GIT_COLOR_NEVER;
		if (use_stdout)
			die(_("standard output, or directory, which one?"));
		if (mkdir(output_directory, 0777) < 0 && errno != EEXIST)
			die_errno(_("Could not create directory '%s'"),
				  output_directory);
	}
