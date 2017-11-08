void format_display_notes(const unsigned char *object_sha1,
			  struct strbuf *sb, const char *output_encoding, int raw)
{
	int i;
	assert(display_notes_trees);
	for (i = 0; display_notes_trees[i]; i++)
		format_note(display_notes_trees[i], object_sha1, sb,
			    output_encoding, raw);
}