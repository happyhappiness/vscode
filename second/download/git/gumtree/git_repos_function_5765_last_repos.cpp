static void set_option(struct transport *transport, const char *name, const char *value)
{
	int r = transport_set_option(transport, name, value);
	if (r < 0)
		die(_("Option \"%s\" value \"%s\" is not valid for %s"),
		    name, value, transport->url);
	if (r > 0)
		warning(_("Option \"%s\" is ignored for %s\n"),
			name, transport->url);
}