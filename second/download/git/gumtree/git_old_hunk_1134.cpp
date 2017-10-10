
	path = ntr + 41;  /* at the beginning of name */
	if (!nul_term_line && path[0] == '"') {
		struct strbuf p_uq = STRBUF_INIT;
		if (unquote_c_style(&p_uq, path, NULL))
			die("invalid quoting");
		path = strbuf_detach(&p_uq, NULL);
	}

	/*
	 * Object type is redundantly derivable three ways.
	 * These should all agree.
	 */
