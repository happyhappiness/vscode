fprintf(stderr, "%s %s... %s\n", msg,
		find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV), sb.buf);