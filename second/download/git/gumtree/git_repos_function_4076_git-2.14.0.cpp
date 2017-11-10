int transport_helper_init(struct transport *transport, const char *name)
{
	struct helper_data *data = xcalloc(1, sizeof(*data));
	data->name = name;

	transport_check_allowed(name);

	if (getenv("GIT_TRANSPORT_HELPER_DEBUG"))
		debug = 1;

	transport->data = data;
	transport->set_option = set_helper_option;
	transport->get_refs_list = get_refs_list;
	transport->fetch = fetch;
	transport->push_refs = push_refs;
	transport->disconnect = release_helper;
	transport->connect = connect_helper;
	transport->smart_options = &(data->transport_options);
	return 0;
}