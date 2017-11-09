static void standard_options(struct transport *t)
{
	char buf[16];
	int v = t->verbose;

	set_helper_option(t, "progress", t->progress ? "true" : "false");

	xsnprintf(buf, sizeof(buf), "%d", v + 1);
	set_helper_option(t, "verbosity", buf);

	switch (t->family) {
	case TRANSPORT_FAMILY_ALL:
		/*
		 * this is already the default,
		 * do not break old remote helpers by setting "all" here
		 */
		break;
	case TRANSPORT_FAMILY_IPV4:
		set_helper_option(t, "family", "ipv4");
		break;
	case TRANSPORT_FAMILY_IPV6:
		set_helper_option(t, "family", "ipv6");
		break;
	}
}