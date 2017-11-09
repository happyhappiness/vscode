int transport_set_option(struct transport *transport,
			 const char *name, const char *value)
{
	int git_reports = 1, protocol_reports = 1;

	if (transport->smart_options)
		git_reports = set_git_option(transport->smart_options,
					     name, value);

	if (transport->set_option)
		protocol_reports = transport->set_option(transport, name,
							value);

	/* If either report is 0, report 0 (success). */
	if (!git_reports || !protocol_reports)
		return 0;
	/* If either reports -1 (invalid value), report -1. */
	if ((git_reports == -1) || (protocol_reports == -1))
		return -1;
	/* Otherwise if both report unknown, report unknown. */
	return 1;
}