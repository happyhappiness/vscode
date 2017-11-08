static int show_abbrev(const struct object_id *oid, void *cb_data)
{
	show_rev(NORMAL, oid, NULL);
	return 0;
}