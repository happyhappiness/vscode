
	printf("\n");

	show_progress();
}

static void *anonymize_tag(const void *old, size_t *len)
{
	static int counter;
	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "tag message %d", counter++);
	return strbuf_detach(&out, len);
}

static void handle_tail(struct object_array *commits, struct rev_info *revs)
{
	struct commit *commit;
	while (commits->nr) {
		commit = (struct commit *)commits->objects[commits->nr - 1].item;
		if (has_unshown_parent(commit))
