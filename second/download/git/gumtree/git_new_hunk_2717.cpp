
	if (verbose || /* Truncate the message just before the diff, if any. */
	    cleanup_mode == CLEANUP_SCISSORS)
		wt_status_truncate_message_at_cut_line(&sb);

	if (cleanup_mode != CLEANUP_NONE)
		strbuf_stripspace(&sb, cleanup_mode == CLEANUP_ALL);
	if (template_untouched(&sb) && !allow_empty_message) {
		rollback_index_files();
		fprintf(stderr, _("Aborting commit; you did not edit the message.\n"));
		exit(1);
	}
	if (message_is_empty(&sb) && !allow_empty_message) {
