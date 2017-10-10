 		if (show_progress > 0)
 			die(_("--progress can't be used with --incremental or porcelain formats"));
 		show_progress = 0;
 	} else if (show_progress < 0)
 		show_progress = isatty(2);
 
-	if (0 < abbrev)
+	if (0 < abbrev && abbrev < GIT_SHA1_HEXSZ)
 		/* one more abbrev length is needed for the boundary commit */
 		abbrev++;
+	else if (!abbrev)
+		abbrev = GIT_SHA1_HEXSZ;
 
 	if (revs_file && read_ancestry(revs_file))
 		die_errno("reading graft file '%s' failed", revs_file);
 
 	if (cmd_is_annotate) {
 		output_option |= OUTPUT_ANNOTATE_COMPAT;
