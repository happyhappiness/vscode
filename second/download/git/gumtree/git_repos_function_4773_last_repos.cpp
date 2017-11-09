void format_display_notes(const struct object_id *object_oid,
			  struct strbuf *sb, const char *output_encoding, int raw)
{
	int i;
	assert(display_notes_trees);
	for (i = 0; display_notes_trees[i]; i++)
		format_note(display_notes_trees[i], object_oid, sb,
			    output_encoding, raw);
}