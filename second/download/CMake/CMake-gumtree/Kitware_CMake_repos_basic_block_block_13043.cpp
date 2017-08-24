((uri = xmemmem(val, eol - val, "://", 3U)) == NULL) {
		/* not touching that! */
		return res;
	}