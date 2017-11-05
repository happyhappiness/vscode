static int edit_patch(int argc, const char **argv, const char *prefix)
{
	char *file = git_pathdup("ADD_EDIT.patch");
	const char *apply_argv[] = { "apply", "--recount", "--cached",
		NULL, NULL };
	struct child_process child = CHILD_PROCESS_INIT;
	struct rev_info rev;
	int out;
	struct stat st;

	apply_argv[3] = file;

	git_config(git_diff_basic_config, NULL); /* no "diff" UI options */

	if (read_cache() < 0)
		die(_("Could not read the index"));

	init_revisions(&rev, prefix);
	rev.diffopt.context = 7;

	argc = setup_revisions(argc, argv, &rev, NULL);
	rev.diffopt.output_format = DIFF_FORMAT_PATCH;
	rev.diffopt.use_color = 0;
	DIFF_OPT_SET(&rev.diffopt, IGNORE_DIRTY_SUBMODULES);
	out = open(file, O_CREAT | O_WRONLY, 0666);
	if (out < 0)
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

	child.git_cmd = 1;
	child.argv = apply_argv;
	if (run_command(&child))
		die(_("Could not apply '%s'"), file);

	unlink(file);
	free(file);
	return 0;
}