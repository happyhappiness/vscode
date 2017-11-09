static int add_one_reference(struct string_list_item *item, void *cb_data)
{
	struct strbuf err = STRBUF_INIT;
	int *required = cb_data;
	char *ref_git = compute_alternate_path(item->string, &err);

	if (!ref_git) {
		if (*required)
			die("%s", err.buf);
		else
			fprintf(stderr,
				_("info: Could not add alternate for '%s': %s\n"),
				item->string, err.buf);
	} else {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addf(&sb, "%s/objects", ref_git);
		add_to_alternates_file(sb.buf);
		strbuf_release(&sb);
	}

	strbuf_release(&err);
	free(ref_git);
	return 0;
}