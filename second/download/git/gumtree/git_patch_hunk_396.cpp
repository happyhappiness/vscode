 	o.remote_ref = remote_ref.buf;
 
 	t = init_notes_check("merge", NOTES_INIT_WRITABLE);
 
 	if (strategy) {
 		if (parse_notes_merge_strategy(strategy, &o.strategy)) {
-			error(_("Unknown -s/--strategy: %s"), strategy);
+			error(_("unknown -s/--strategy: %s"), strategy);
 			usage_with_options(git_notes_merge_usage, options);
 		}
 	} else {
 		struct strbuf merge_key = STRBUF_INIT;
 		const char *short_ref = NULL;
 
