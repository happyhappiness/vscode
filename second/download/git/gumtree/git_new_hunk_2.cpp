			die_errno(_("could not read log file '%s'"),
				  logfile);
		hook_arg1 = "message";
	} else if (use_message) {
		char *buffer;
		buffer = strstr(use_message_buffer, "\n\n");
		if (buffer)
			strbuf_add(&sb, buffer + 2, strlen(buffer + 2));
		hook_arg1 = "commit";
		hook_arg2 = use_message;
	} else if (fixup_message) {
		struct pretty_print_context ctx = {0};
		struct commit *commit;
		commit = lookup_commit_reference_by_name(fixup_message);
