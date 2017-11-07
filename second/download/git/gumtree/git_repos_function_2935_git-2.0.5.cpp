static int get_exporter(struct transport *transport,
			struct child_process *fastexport,
			struct string_list *revlist_args)
{
	struct helper_data *data = transport->data;
	struct child_process *helper = get_helper(transport);
	int argc = 0, i;
	struct strbuf tmp = STRBUF_INIT;

	memset(fastexport, 0, sizeof(*fastexport));

	/* we need to duplicate helper->in because we want to use it after
	 * fastexport is done with it. */
	fastexport->out = dup(helper->in);
	fastexport->argv = xcalloc(6 + revlist_args->nr, sizeof(*fastexport->argv));
	fastexport->argv[argc++] = "fast-export";
	fastexport->argv[argc++] = "--use-done-feature";
	fastexport->argv[argc++] = data->signed_tags ?
		"--signed-tags=verbatim" : "--signed-tags=warn-strip";
	if (data->export_marks) {
		strbuf_addf(&tmp, "--export-marks=%s.tmp", data->export_marks);
		fastexport->argv[argc++] = strbuf_detach(&tmp, NULL);
	}
	if (data->import_marks) {
		strbuf_addf(&tmp, "--import-marks=%s", data->import_marks);
		fastexport->argv[argc++] = strbuf_detach(&tmp, NULL);
	}

	for (i = 0; i < revlist_args->nr; i++)
		fastexport->argv[argc++] = revlist_args->items[i].string;

	fastexport->git_cmd = 1;
	return start_command(fastexport);
}