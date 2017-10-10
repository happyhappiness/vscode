		char *split_args;
		const char **argv;
		int code;
		int count;

		fprintf(stderr, "git> ");
		if (strbuf_getline_lf(&line, stdin) == EOF) {
			fprintf(stderr, "\n");
			strbuf_release(&line);
			break;
		}
		strbuf_trim(&line);
		rawargs = strbuf_detach(&line, NULL);
