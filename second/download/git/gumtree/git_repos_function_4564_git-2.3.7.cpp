static int both_empty(struct name_entry *a, struct name_entry *b)
{
	return !(a->sha1 || b->sha1);
}