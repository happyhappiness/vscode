static void add_to_tip_table(const struct object_id *oid, const char *refname,
			     int shorten_unambiguous)
{
	refname = name_ref_abbrev(refname, shorten_unambiguous);

	ALLOC_GROW(tip_table.table, tip_table.nr + 1, tip_table.alloc);
	oidcpy(&tip_table.table[tip_table.nr].oid, oid);
	tip_table.table[tip_table.nr].refname = xstrdup(refname);
	tip_table.nr++;
	tip_table.sorted = 0;
}