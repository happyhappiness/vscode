 
 	if (revs_file && read_ancestry(revs_file))
 		die_errno("reading graft file '%s' failed", revs_file);
 
 	if (cmd_is_annotate) {
 		output_option |= OUTPUT_ANNOTATE_COMPAT;
-		blame_date_mode = DATE_ISO8601;
+		blame_date_mode.type = DATE_ISO8601;
 	} else {
 		blame_date_mode = revs.date_mode;
 	}
 
 	/* The maximum width used to show the dates */
-	switch (blame_date_mode) {
+	switch (blame_date_mode.type) {
 	case DATE_RFC2822:
 		blame_date_width = sizeof("Thu, 19 Oct 2006 16:00:04 -0700");
 		break;
 	case DATE_ISO8601_STRICT:
 		blame_date_width = sizeof("2006-10-19T16:00:04-07:00");
 		break;
