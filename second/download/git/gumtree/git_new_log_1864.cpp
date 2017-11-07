fprintf(stderr, "%s %s... %s\n", msg,
		find_unique_abbrev(commit->object.oid.hash, DEFAULT_ABBREV), sb.buf);