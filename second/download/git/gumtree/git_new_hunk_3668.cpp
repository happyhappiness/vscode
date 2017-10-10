	while ((commit = get_revision(&rev)) != NULL) {
		strbuf_addch(&out, '\n');
		strbuf_addf(&out, "commit %s\n",
			oid_to_hex(&commit->object.oid));
		pretty_print_commit(&ctx, commit, &out);
	}
	write_file_buf(git_path_squash_msg(), out.buf, out.len);
	strbuf_release(&out);
}

static void finish(struct commit *head_commit,
		   struct commit_list *remoteheads,
		   const unsigned char *new_head, const char *msg)
