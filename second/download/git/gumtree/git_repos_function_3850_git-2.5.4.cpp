void expand_notes_ref(struct strbuf *sb)
{
	if (starts_with(sb->buf, "refs/notes/"))
		return; /* we're happy */
	else if (starts_with(sb->buf, "notes/"))
		strbuf_insert(sb, 0, "refs/", 5);
	else
		strbuf_insert(sb, 0, "refs/notes/", 11);
}