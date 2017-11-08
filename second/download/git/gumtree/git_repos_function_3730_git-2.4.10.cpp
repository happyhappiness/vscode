static int non_note_cmp(const struct non_note *a, const struct non_note *b)
{
	return strcmp(a->path, b->path);
}