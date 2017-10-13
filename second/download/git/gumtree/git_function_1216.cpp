static void append_merge_parents(struct commit_list **tail)
{
	int merge_head;
	struct strbuf line = STRBUF_INIT;

	merge_head = open(git_path_merge_head(), O_RDONLY);
	if (merge_head < 0) {
		if (errno == ENOENT)
			return;
		die("cannot open '%s' for reading", git_path_merge_head());
	}

	while (!strbuf_getwholeline_fd(&line, merge_head, '\n')) {
		struct object_id oid;
		if (line.len < GIT_SHA1_HEXSZ || get_oid_hex(line.buf, &oid))
			die("unknown line in '%s': %s", git_path_merge_head(), line.buf);
		tail = append_parent(tail, &oid);
	}
	close(merge_head);
	strbuf_release(&line);
}