static struct complete_reflogs *read_complete_reflog(const char *ref)
{
	struct complete_reflogs *reflogs =
		xcalloc(1, sizeof(struct complete_reflogs));
	reflogs->ref = xstrdup(ref);
	for_each_reflog_ent(ref, read_one_reflog, reflogs);
	if (reflogs->nr == 0) {
		unsigned char sha1[20];
		const char *name;
		void *name_to_free;
		name = name_to_free = resolve_refdup(ref, sha1, 1, NULL);
		if (name) {
			for_each_reflog_ent(name, read_one_reflog, reflogs);
			free(name_to_free);
		}
	}
	if (reflogs->nr == 0) {
		int len = strlen(ref);
		char *refname = xmalloc(len + 12);
		sprintf(refname, "refs/%s", ref);
		for_each_reflog_ent(refname, read_one_reflog, reflogs);
		if (reflogs->nr == 0) {
			sprintf(refname, "refs/heads/%s", ref);
			for_each_reflog_ent(refname, read_one_reflog, reflogs);
		}
		free(refname);
	}
	return reflogs;
}