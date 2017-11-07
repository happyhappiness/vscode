void commit_notes(struct notes_tree *t, const char *msg)
{
	struct strbuf buf = STRBUF_INIT;
	unsigned char commit_sha1[20];

	if (!t)
		t = &default_notes_tree;
	if (!t->initialized || !t->ref || !*t->ref)
		die(_("Cannot commit uninitialized/unreferenced notes tree"));
	if (!t->dirty)
		return; /* don't have to commit an unchanged tree */

	/* Prepare commit message and reflog message */
	strbuf_addstr(&buf, msg);
	if (buf.buf[buf.len - 1] != '\n')
		strbuf_addch(&buf, '\n'); /* Make sure msg ends with newline */

	create_notes_commit(t, NULL, buf.buf, buf.len, commit_sha1);
	strbuf_insert(&buf, 0, "notes: ", 7); /* commit message starts at index 7 */
	update_ref(buf.buf, t->ref, commit_sha1, NULL, 0, DIE_ON_ERR);

	strbuf_release(&buf);
}