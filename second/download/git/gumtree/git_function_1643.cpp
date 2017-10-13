static void report_refname_conflict(struct ref_entry *entry,
				    const char *refname)
{
	error("'%s' exists; cannot create '%s'", entry->name, refname);
}