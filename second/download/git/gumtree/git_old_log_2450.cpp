printf("%c %s %s\n", sign,
		       find_unique_abbrev(commit->object.sha1, abbrev),
		       buf.buf);