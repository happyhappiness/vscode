static void add_head_info(struct strbuf *head_ref, struct worktree *worktree)
{
	if (head_ref->len) {
		if (worktree->is_detached) {
			get_sha1_hex(head_ref->buf, worktree->head_sha1);
		} else {
			resolve_ref_unsafe(head_ref->buf, 0, worktree->head_sha1, NULL);
			worktree->head_ref = strbuf_detach(head_ref, NULL);
		}
	}
}