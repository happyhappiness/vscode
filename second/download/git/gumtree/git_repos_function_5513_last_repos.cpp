static void get_default_heads(void)
{
	if (head_points_at && !is_null_oid(&head_oid))
		fsck_handle_ref("HEAD", &head_oid, 0, NULL);
	for_each_rawref(fsck_handle_ref, NULL);
	if (include_reflogs)
		for_each_reflog(fsck_handle_reflog, NULL);

	/*
	 * Not having any default heads isn't really fatal, but
	 * it does mean that "--unreachable" no longer makes any
	 * sense (since in this case everything will obviously
	 * be unreachable by definition.
	 *
	 * Showing dangling objects is valid, though (as those
	 * dangling objects are likely lost heads).
	 *
	 * So we just print a warning about it, and clear the
	 * "show_unreachable" flag.
	 */
	if (!default_refs) {
		fprintf(stderr, "notice: No default references\n");
		show_unreachable = 0;
	}
}