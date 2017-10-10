	unsigned flags;
};

static int write_one_shallow(const struct commit_graft *graft, void *cb_data)
{
	struct write_shallow_data *data = cb_data;
	const char *hex = sha1_to_hex(graft->sha1);
	if (graft->nr_parent != -1)
		return 0;
	if (data->flags & SEEN_ONLY) {
		struct commit *c = lookup_commit(graft->sha1);
		if (!c || !(c->object.flags & SEEN)) {
			if (data->flags & VERBOSE)
				printf("Removing %s from .git/shallow\n",
				       sha1_to_hex(c->object.sha1));
			return 0;
		}
