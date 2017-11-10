static void debug_stage(const char *label, const struct cache_entry *ce,
			struct unpack_trees_options *o)
{
	printf("%s ", label);
	if (!ce)
		printf("(missing)\n");
	else if (ce == o->df_conflict_entry)
		printf("(conflict)\n");
	else
		printf("%06o #%d %s %.8s\n",
		       ce->ce_mode, ce_stage(ce), ce->name,
		       oid_to_hex(&ce->oid));
}