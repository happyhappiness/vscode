		    INDEX_FORMAT_UB < preferred_index_format)
			die("index-version %d not in range: %d..%d",
			    preferred_index_format,
			    INDEX_FORMAT_LB, INDEX_FORMAT_UB);

		if (the_index.version != preferred_index_format)
			active_cache_changed |= SOMETHING_CHANGED;
		the_index.version = preferred_index_format;
	}

	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT, nbuf = STRBUF_INIT;

