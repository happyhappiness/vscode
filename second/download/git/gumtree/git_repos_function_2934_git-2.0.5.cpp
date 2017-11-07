static int get_importer(struct transport *transport, struct child_process *fastimport)
{
	struct child_process *helper = get_helper(transport);
	struct helper_data *data = transport->data;
	struct argv_array argv = ARGV_ARRAY_INIT;
	int cat_blob_fd, code;
	memset(fastimport, 0, sizeof(*fastimport));
	fastimport->in = helper->out;
	argv_array_push(&argv, "fast-import");
	argv_array_push(&argv, debug ? "--stats" : "--quiet");

	if (data->bidi_import) {
		cat_blob_fd = xdup(helper->in);
		argv_array_pushf(&argv, "--cat-blob-fd=%d", cat_blob_fd);
	}
	fastimport->argv = argv.argv;
	fastimport->git_cmd = 1;

	code = start_command(fastimport);
	return code;
}