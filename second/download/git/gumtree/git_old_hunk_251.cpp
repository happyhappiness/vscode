static int push_refs_with_export(struct transport *transport,
		struct ref *remote_refs, int flags)
{
	struct ref *ref;
	struct child_process *helper, exporter;
	struct helper_data *data = transport->data;
	struct string_list revlist_args = STRING_LIST_INIT_NODUP;
	struct strbuf buf = STRBUF_INIT;

	if (!data->refspecs)
		die("remote-helper doesn't support push; refspec needed");

	if (flags & TRANSPORT_PUSH_DRY_RUN) {
