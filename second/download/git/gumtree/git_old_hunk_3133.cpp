		if (changed)
			pretty_print_dels();

		clean_print_color(CLEAN_COLOR_PROMPT);
		printf(_("Input ignore patterns>> "));
		clean_print_color(CLEAN_COLOR_RESET);
		if (strbuf_getline(&confirm, stdin, '\n') != EOF)
			strbuf_trim(&confirm);
		else
			putchar('\n');

		/* quit filter_by_pattern mode if press ENTER or Ctrl-D */
		if (!confirm.len)
