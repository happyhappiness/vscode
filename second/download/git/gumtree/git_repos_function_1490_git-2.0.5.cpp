void foreach_alt_odb(alt_odb_fn fn, void *cb)
{
	struct alternate_object_database *ent;

	prepare_alt_odb();
	for (ent = alt_odb_list; ent; ent = ent->next)
		if (fn(ent, cb))
			return;
}