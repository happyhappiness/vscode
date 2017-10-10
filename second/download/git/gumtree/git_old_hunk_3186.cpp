			else
				error("unknown switch '%c'", *ctx.opt);
			usage_with_options(update_index_usage, options);
		}
	}
	argc = parse_options_end(&ctx);
	if (preferred_index_format) {
		if (preferred_index_format < INDEX_FORMAT_LB ||
		    INDEX_FORMAT_UB < preferred_index_format)
			die("index-version %d not in range: %d..%d",
			    preferred_index_format,
			    INDEX_FORMAT_LB, INDEX_FORMAT_UB);
