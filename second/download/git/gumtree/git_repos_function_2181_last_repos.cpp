int foreach_alt_odb(alt_odb_fn fn, void *cb)
{
	struct alternate_object_database *ent;
	int r = 0;

	prepare_alt_odb();
	for (ent = alt_odb_list; ent; ent = ent->next) {
		r = fn(ent, cb);
		if (r)
			break;
	}
	return r;
}