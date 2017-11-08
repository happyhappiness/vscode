static int get_exporter(struct transport *transport,
			struct child_process *fastexport,
			struct string_list *revlist_args)
{
	struct helper_data *data = transport->data;
	struct child_process *helper = get_helper(transport);
	int i;

	child_process_init(fastexport);

	/* we need to duplicate helper->in because we want to use it after
	 * fastexport is done with it. */
	fastexport->out = dup(helper->in);
	argv_array_push(&fastexport->args, "fast-export");
	argv_array_push(&fastexport->args, "--use-done-feature");
	argv_array_push(&fastexport->args, data->signed_tags ?
		"--signed-tags=verbatim" : "--signed-tags=warn-strip");
	if (data->export_marks)
		argv_array_pushf(&fastexport->args, "--export-marks=%s.tmp", data->export_marks);
	if (data->import_marks)
		argv_array_pushf(&fastexport->args, "--import-marks=%s", data->import_marks);

	for (i = 0; i < revlist_args->nr; i++)
		argv_array_push(&fastexport->args, revlist_args->items[i].string);

	fastexport->git_cmd = 1;
	return start_command(fastexport);
}