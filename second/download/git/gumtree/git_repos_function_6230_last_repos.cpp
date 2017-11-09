static void write_merge_state(struct commit_list *remoteheads)
{
	write_merge_heads(remoteheads);
	strbuf_addch(&merge_msg, '\n');
	write_file_buf(git_path_merge_msg(), merge_msg.buf, merge_msg.len);
}