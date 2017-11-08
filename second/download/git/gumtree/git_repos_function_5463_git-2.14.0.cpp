static int both_empty(struct name_entry *a, struct name_entry *b)
{
	return !(a->oid || b->oid);
}