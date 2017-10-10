 		error(_("unrecognized argument: %s"), argv[1]);
 		usage_with_options(shortlog_usage, options);
 	}
 
 	log.user_format = rev.commit_format == CMIT_FMT_USERFORMAT;
 	log.abbrev = rev.abbrev;
+	log.file = rev.diffopt.file;
 
 	/* assume HEAD if from a tty */
 	if (!nongit && !rev.pending.nr && isatty(0))
 		add_head_to_pending(&rev);
 	if (rev.pending.nr == 0) {
 		if (isatty(0))
