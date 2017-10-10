			ctx.output_encoding = get_commit_output_encoding();
			format_commit_message(c, "squash! %s\n\n", &sb,
					      &ctx);
		}
	}

	if (message.len) {
		strbuf_addbuf(&sb, &message);
		hook_arg1 = "message";
	} else if (logfile && !strcmp(logfile, "-")) {
		if (isatty(0))
			fprintf(stderr, _("(reading log message from standard input)\n"));
		if (strbuf_read(&sb, 0, 0) < 0)
