void expand_loose_notes_ref(struct strbuf *sb)
{
	unsigned char object[20];

	if (get_sha1(sb->buf, object)) {
		/* fallback to expand_notes_ref */
		expand_notes_ref(sb);
	}
}