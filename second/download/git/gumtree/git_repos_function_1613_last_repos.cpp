static int diff_populate_gitlink(struct diff_filespec *s, int size_only)
{
	struct strbuf buf = STRBUF_INIT;
	char *dirty = "";

	/* Are we looking at the work tree? */
	if (s->dirty_submodule)
		dirty = "-dirty";

	strbuf_addf(&buf, "Subproject commit %s%s\n",
		    oid_to_hex(&s->oid), dirty);
	s->size = buf.len;
	if (size_only) {
		s->data = NULL;
		strbuf_release(&buf);
	} else {
		s->data = strbuf_detach(&buf, NULL);
		s->should_free = 1;
	}
	return 0;
}