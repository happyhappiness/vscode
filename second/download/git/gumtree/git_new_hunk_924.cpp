	write_file_buf(git_path_squash_msg(), out.buf, out.len);
	strbuf_release(&out);
}

static void finish(struct commit *head_commit,
		   struct commit_list *remoteheads,
		   const struct object_id *new_head, const char *msg)
{
	struct strbuf reflog_message = STRBUF_INIT;
	const struct object_id *head = &head_commit->object.oid;

	if (!msg)
		strbuf_addstr(&reflog_message, getenv("GIT_REFLOG_ACTION"));
	else {
		if (verbosity >= 0)
			printf("%s\n", msg);
