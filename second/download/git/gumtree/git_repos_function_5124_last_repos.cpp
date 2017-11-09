static int tipcmp(const void *a_, const void *b_)
{
	const struct tip_table_entry *a = a_, *b = b_;
	return oidcmp(&a->oid, &b->oid);
}