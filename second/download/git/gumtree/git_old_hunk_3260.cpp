	set_helper_option(t, "progress", t->progress ? "true" : "false");

	n = snprintf(buf, sizeof(buf), "%d", v + 1);
	if (n >= sizeof(buf))
		die("impossibly large verbosity value");
	set_helper_option(t, "verbosity", buf);
}

static int release_helper(struct transport *transport)
{
	int res = 0;
	struct helper_data *data = transport->data;
