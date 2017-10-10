	display_progress(progress, 256);
	stop_progress(&progress);
}

static int fsck_head_link(void)
{
	int null_is_error = 0;

	if (verbose)
		fprintf(stderr, "Checking HEAD link\n");

	head_points_at = resolve_ref_unsafe("HEAD", 0, head_oid.hash, NULL);
	if (!head_points_at) {
		errors_found |= ERROR_REFS;
		return error("Invalid HEAD");
	}
	if (!strcmp(head_points_at, "HEAD"))
		/* detached HEAD */
