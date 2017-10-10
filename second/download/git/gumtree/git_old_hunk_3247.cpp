		char *split_args;
		const char **argv;
		int code;
		int count;

		fprintf(stderr, "git> ");
		if (strbuf_getline(&line, stdin, '\n') == EOF) {
			fprintf(stderr, "\n");
			strbuf_release(&line);
			break;
		}
		strbuf_trim(&line);
		rawargs = strbuf_detach(&line, NULL);
