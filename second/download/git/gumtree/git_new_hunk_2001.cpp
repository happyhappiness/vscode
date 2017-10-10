		die(_("Cannot commit uninitialized/unreferenced notes tree"));
	if (!t->dirty)
		return; /* don't have to commit an unchanged tree */

	/* Prepare commit message and reflog message */
	strbuf_addstr(&buf, msg);
	strbuf_complete_line(&buf);

	create_notes_commit(t, NULL, buf.buf, buf.len, commit_sha1);
	strbuf_insert(&buf, 0, "notes: ", 7); /* commit message starts at index 7 */
	update_ref(buf.buf, t->ref, commit_sha1, NULL, 0,
		   UPDATE_REFS_DIE_ON_ERR);

