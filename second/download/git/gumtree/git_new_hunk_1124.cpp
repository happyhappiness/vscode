		rollback_index_files();
		die(_("could not read commit message: %s"), strerror(saved_errno));
	}

	if (verbose || /* Truncate the message just before the diff, if any. */
	    cleanup_mode == CLEANUP_SCISSORS)
		strbuf_setlen(&sb, wt_status_locate_end(sb.buf, sb.len));

	if (cleanup_mode != CLEANUP_NONE)
		strbuf_stripspace(&sb, cleanup_mode == CLEANUP_ALL);
	if (template_untouched(&sb) && !allow_empty_message) {
		rollback_index_files();
		fprintf(stderr, _("Aborting commit; you did not edit the message.\n"));
