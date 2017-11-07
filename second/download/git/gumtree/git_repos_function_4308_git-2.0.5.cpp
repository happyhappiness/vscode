static int same_entry(struct name_entry *a, struct name_entry *b)
{
	return	a->sha1 &&
		b->sha1 &&
		!hashcmp(a->sha1, b->sha1) &&
		a->mode == b->mode;
}