static void fsck_object_dir(const char *path)
{
	struct progress *progress = NULL;

	if (verbose)
		fprintf(stderr, "Checking object directory\n");

	if (show_progress)
		progress = start_progress(_("Checking object directories"), 256);

	for_each_loose_file_in_objdir(path, fsck_loose, fsck_cruft, fsck_subdir,
				      progress);
	display_progress(progress, 256);
	stop_progress(&progress);
}