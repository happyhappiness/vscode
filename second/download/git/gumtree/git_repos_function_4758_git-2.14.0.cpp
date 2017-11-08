void expand_loose_notes_ref(struct strbuf *sb)
{
	struct object_id object;

	if (get_oid(sb->buf, &object)) {
		/* fallback to expand_notes_ref */
		expand_notes_ref(sb);
	}
}