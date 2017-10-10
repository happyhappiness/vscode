		fflush(stdout);
		response = get_response_line();
		if (parse_cat_response_line(response, &preimage.max_off))
			die("invalid cat-blob response: %s", response);
		check_preimage_overflow(preimage.max_off, 1);
	}
	if (old_mode == S_IFLNK) {
		strbuf_addstr(&preimage.buf, "link ");
		check_preimage_overflow(preimage.max_off, strlen("link "));
		preimage.max_off += strlen("link ");
		check_preimage_overflow(preimage.max_off, 1);
	}
	if (svndiff0_apply(input, len, &preimage, out))
