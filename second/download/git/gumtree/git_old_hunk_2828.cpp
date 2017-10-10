	if (!default_refs) {
		fprintf(stderr, "notice: No default references\n");
		show_unreachable = 0;
	}
}

static void fsck_object_dir(const char *path)
{
	int i;
	struct progress *progress = NULL;

	if (verbose)
		fprintf(stderr, "Checking object directory\n");

	if (show_progress)
		progress = start_progress(_("Checking object directories"), 256);
	for (i = 0; i < 256; i++) {
		static char dir[4096];
		sprintf(dir, "%s/%02x", path, i);
		fsck_dir(i, dir);
		display_progress(progress, i+1);
	}
	stop_progress(&progress);
	fsck_sha1_list();
}

static int fsck_head_link(void)
{
	int flag;
	int null_is_error = 0;
