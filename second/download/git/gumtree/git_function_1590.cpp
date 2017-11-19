static void dump_tags(void)
{
	static const char *msg = "fast-import";
	struct tag *t;
	struct ref_lock *lock;
	struct strbuf ref_name = STRBUF_INIT;

	for (t = first_tag; t; t = t->next_tag) {
		strbuf_reset(&ref_name);
		strbuf_addf(&ref_name, "tags/%s", t->name);
		lock = lock_ref_sha1(ref_name.buf, NULL);
		if (!lock || write_ref_sha1(lock, t->sha1, msg) < 0)
			failure |= error("Unable to update %s", ref_name.buf);
	}
	strbuf_release(&ref_name);
}