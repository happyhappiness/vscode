static void display_error_msgs(struct unpack_trees_options *o)
{
	int e, i;
	int something_displayed = 0;
	for (e = 0; e < NB_UNPACK_TREES_ERROR_TYPES; e++) {
		struct string_list *rejects = &o->unpack_rejects[e];
		if (rejects->nr > 0) {
			struct strbuf path = STRBUF_INIT;
			something_displayed = 1;
			for (i = 0; i < rejects->nr; i++)
				strbuf_addf(&path, "\t%s\n", rejects->items[i].string);
			error(ERRORMSG(o, e), path.buf);
			strbuf_release(&path);
		}
		string_list_clear(rejects, 0);
	}
	if (something_displayed)
		fprintf(stderr, _("Aborting\n"));
}