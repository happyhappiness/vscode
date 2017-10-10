{
	struct write_shallow_data *data = cb_data;
	const char *hex = oid_to_hex(&graft->oid);
	if (graft->nr_parent != -1)
		return 0;
	if (data->flags & SEEN_ONLY) {
		struct commit *c = lookup_commit(&graft->oid);
		if (!c || !(c->object.flags & SEEN)) {
			if (data->flags & VERBOSE)
				printf("Removing %s from .git/shallow\n",
				       oid_to_hex(&c->object.oid));
			return 0;
		}
