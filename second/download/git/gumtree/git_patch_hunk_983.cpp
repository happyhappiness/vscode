 		ret = list_tags(&filter, sorting, format);
 		if (column_active(colopts))
 			stop_column_filter();
 		return ret;
 	}
 	if (filter.lines != -1)
-		die(_("-n option is only allowed with -l."));
+		die(_("-n option is only allowed in list mode"));
 	if (filter.with_commit)
-		die(_("--contains option is only allowed with -l."));
+		die(_("--contains option is only allowed in list mode"));
+	if (filter.no_commit)
+		die(_("--no-contains option is only allowed in list mode"));
 	if (filter.points_at.nr)
-		die(_("--points-at option is only allowed with -l."));
+		die(_("--points-at option is only allowed in list mode"));
 	if (filter.merge_commit)
-		die(_("--merged and --no-merged option are only allowed with -l"));
+		die(_("--merged and --no-merged options are only allowed in list mode"));
 	if (cmdmode == 'd')
 		return for_each_tag_name(argv, delete_tag, NULL);
 	if (cmdmode == 'v') {
 		if (format)
 			verify_ref_format(format);
 		return for_each_tag_name(argv, verify_tag, format);
