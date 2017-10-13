fprintf(file, "%c %s %s\n", sign,
		       find_unique_abbrev(commit->object.oid.hash, abbrev),
		       buf.buf);