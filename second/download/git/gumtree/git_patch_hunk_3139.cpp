 		usage_with_options(builtin_column_usage, options);
 	if (real_command || command) {
 		if (!real_command || !command || strcmp(real_command, command))
 			die(_("--command must be the first argument"));
 	}
 	finalize_colopts(&colopts, -1);
-	while (!strbuf_getline(&sb, stdin, '\n'))
+	while (!strbuf_getline(&sb, stdin))
 		string_list_append(&list, sb.buf);
 
 	print_columns(&list, colopts, &copts);
 	return 0;
 }
