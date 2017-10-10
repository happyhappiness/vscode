 	}
 	if (buf.len == 0) {
 		string_list_clear(&cas_options, 0);
 		return 0;
 	}
 
-	standard_options(transport);
 	for_each_string_list_item(cas_option, &cas_options)
 		set_helper_option(transport, "cas", cas_option->string);
 
 	if (flags & TRANSPORT_PUSH_DRY_RUN) {
 		if (set_helper_option(transport, "dry-run", "true") != 0)
 			die("helper %s does not support dry-run", data->name);
