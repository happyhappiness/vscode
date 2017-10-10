		strbuf_addf(&ret->summary, "(%s)", oid_to_hex(&commit->object.oid));

	unuse_commit_buffer(commit, message);
}

/*
 * To allow LF and other nonportable characters in pathnames,
 * they are c-style quoted as needed.
 */
static void write_filename_info(const char *path)
{
	printf("filename ");
	write_name_quoted(path, stdout, '\n');
}

/*
 * Porcelain/Incremental format wants to show a lot of details per
 * commit.  Instead of repeating this every line, emit it only once,
 * the first time each commit appears in the output (unless the
