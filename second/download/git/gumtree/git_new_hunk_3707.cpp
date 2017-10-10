		path = buf.buf;
	}

	if (!access_or_die(path, R_OK, 0)) {
		if (++inc->depth > MAX_INCLUDE_DEPTH)
			die(include_depth_advice, MAX_INCLUDE_DEPTH, path,
			    !cf ? "<unknown>" :
			    cf->name ? cf->name :
			    "the command line");
		ret = git_config_from_file(git_config_include, path, inc);
		inc->depth--;
	}
	strbuf_release(&buf);
	free(expanded);
	return ret;
