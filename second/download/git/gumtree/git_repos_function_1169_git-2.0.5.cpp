static void dump_tags(void)
{
	static const char *msg = "fast-import";
	struct tag *t;
	struct ref_lock *lock;
	char ref_name[PATH_MAX];

	for (t = first_tag; t; t = t->next_tag) {
		sprintf(ref_name, "tags/%s", t->name);
		lock = lock_ref_sha1(ref_name, NULL);
		if (!lock || write_ref_sha1(lock, t->sha1, msg) < 0)
			failure |= error("Unable to update %s", ref_name);
	}
}