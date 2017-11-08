static int anti_reference(const char *refname, const struct object_id *oid, int flag, void *cb_data)
{
	show_rev(REVERSED, oid->hash, refname);
	return 0;
}