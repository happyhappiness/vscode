 	struct string_list revlist_args = STRING_LIST_INIT_DUP;
 	struct strbuf buf = STRBUF_INIT;
 
 	if (!data->refspecs)
 		die("remote-helper doesn't support push; refspec needed");
 
-	if (flags & TRANSPORT_PUSH_DRY_RUN) {
-		if (set_helper_option(transport, "dry-run", "true") != 0)
-			die("helper %s does not support dry-run", data->name);
-	} else if (flags & TRANSPORT_PUSH_CERT) {
-		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "true") != 0)
-			die("helper %s does not support --signed", data->name);
-	}
-
+	set_common_push_options(transport, data->name, flags);
 	if (flags & TRANSPORT_PUSH_FORCE) {
 		if (set_helper_option(transport, "force", "true") != 0)
 			warning("helper %s does not support 'force'", data->name);
 	}
 
 	helper = get_helper(transport);
