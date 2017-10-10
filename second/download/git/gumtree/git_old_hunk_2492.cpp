	return &commit_list_insert(parent, tail)->next;
}

static void append_merge_parents(struct commit_list **tail)
{
	int merge_head;
	const char *merge_head_file = git_path("MERGE_HEAD");
	struct strbuf line = STRBUF_INIT;

	merge_head = open(merge_head_file, O_RDONLY);
	if (merge_head < 0) {
		if (errno == ENOENT)
			return;
		die("cannot open '%s' for reading", merge_head_file);
	}

	while (!strbuf_getwholeline_fd(&line, merge_head, '\n')) {
		unsigned char sha1[20];
		if (line.len < 40 || get_sha1_hex(line.buf, sha1))
			die("unknown line in '%s': %s", merge_head_file, line.buf);
		tail = append_parent(tail, sha1);
	}
	close(merge_head);
	strbuf_release(&line);
}

