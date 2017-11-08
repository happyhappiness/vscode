static struct complete_reflogs *read_complete_reflog(const char *ref)
{
	struct complete_reflogs *reflogs =
		xcalloc(1, sizeof(struct complete_reflogs));
	reflogs->ref = xstrdup(ref);
	for_each_reflog_ent(ref, read_one_reflog, reflogs);
	if (reflogs->nr == 0) {
		struct object_id oid;
		const char *name;
		void *name_to_free;
		name = name_to_free = resolve_refdup(ref, RESOLVE_REF_READING,
						     oid.hash, NULL);
		if (name) {
			for_each_reflog_ent(name, read_one_reflog, reflogs);
			free(name_to_free);
		}
	}
	if (reflogs->nr == 0) {
		char *refname = xstrfmt("refs/%s", ref);
		for_each_reflog_ent(refname, read_one_reflog, reflogs);
		if (reflogs->nr == 0) {
			free(refname);
			refname = xstrfmt("refs/heads/%s", ref);
			for_each_reflog_ent(refname, read_one_reflog, reflogs);
		}
		free(refname);
	}
	return reflogs;
}