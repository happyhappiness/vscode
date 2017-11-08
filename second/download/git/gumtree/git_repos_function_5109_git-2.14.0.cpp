static const unsigned char *nth_tip_table_ent(size_t ix, void *table_)
{
	struct tip_table_entry *table = table_;
	return table[ix].oid.hash;
}