 	if (git_config_rename_section(oldsection.buf, newsection.buf) < 0)
 		die(_("Branch is renamed, but update of config-file failed"));
 	strbuf_release(&oldsection);
 	strbuf_release(&newsection);
 }
 
-static int opt_parse_merge_filter(const struct option *opt, const char *arg, int unset)
-{
-	merge_filter = ((opt->long_name[0] == 'n')
-			? SHOW_NOT_MERGED
-			: SHOW_MERGED);
-	if (unset)
-		merge_filter = SHOW_NOT_MERGED; /* b/c for --no-merged */
-	if (!arg)
-		arg = "HEAD";
-	if (get_sha1(arg, merge_filter_ref))
-		die(_("malformed object name %s"), arg);
-	return 0;
-}
-
 static const char edit_description[] = "BRANCH_DESCRIPTION";
 
 static int edit_branch_description(const char *branch_name)
 {
 	int status;
 	struct strbuf buf = STRBUF_INIT;
