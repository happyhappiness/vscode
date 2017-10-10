#if DEBUG
		fprintf(stderr, "cache-tree update-one %o %.*s\n",
			mode, entlen, path + baselen);
#endif
	}

	if (dryrun)
		hash_sha1_file(buffer.buf, buffer.len, tree_type, it->sha1);
	else if (write_sha1_file(buffer.buf, buffer.len, tree_type, it->sha1)) {
		strbuf_release(&buffer);
		return -1;
	}

