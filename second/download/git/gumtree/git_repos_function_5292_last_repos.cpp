static int show_reference(const char *refname, const struct object_id *oid, int flag, void *cb_data)
{
	if (ref_excluded(ref_excludes, refname))
		return 0;
	show_rev(NORMAL, oid, refname);
	return 0;
}