		if (the_index.version != preferred_index_format)
			active_cache_changed |= SOMETHING_CHANGED;
		the_index.version = preferred_index_format;
	}

	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT;
		struct strbuf unquoted = STRBUF_INIT;

		setup_work_tree();
		while (getline_fn(&buf, stdin) != EOF) {
			char *p;
			if (!nul_term_line && buf.buf[0] == '"') {
				strbuf_reset(&unquoted);
				if (unquote_c_style(&unquoted, buf.buf, NULL))
					die("line is badly quoted");
				strbuf_swap(&buf, &unquoted);
			}
			p = prefix_path(prefix, prefix_length, buf.buf);
			update_one(p);
			if (set_executable_bit)
				chmod_path(set_executable_bit, p);
			free(p);
		}
		strbuf_release(&unquoted);
		strbuf_release(&buf);
	}

	if (split_index > 0) {
		init_split_index(&the_index);
		the_index.cache_changed |= SPLIT_INDEX_ORDERED;
