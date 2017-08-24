((eol = _warc_find_eol(val, buf + bsz - val)) == NULL) {
		/* no end of line */
		return res;
	}