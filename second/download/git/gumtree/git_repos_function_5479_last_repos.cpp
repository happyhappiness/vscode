static int same_entry(struct name_entry *a, struct name_entry *b)
{
	return	a->oid &&
		b->oid &&
		!oidcmp(a->oid, b->oid) &&
		a->mode == b->mode;
}