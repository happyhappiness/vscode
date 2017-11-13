static void set_common_push_options(struct transport *transport,
				   const char *name, int flags)
{
	if (flags & TRANSPORT_PUSH_DRY_RUN) {
		if (set_helper_option(transport, "dry-run", "true") != 0)
			die("helper %s does not support dry-run", name);
	} else if (flags & TRANSPORT_PUSH_CERT_ALWAYS) {
		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "true") != 0)
			die("helper %s does not support --signed", name);
	} else if (flags & TRANSPORT_PUSH_CERT_IF_ASKED) {
		if (set_helper_option(transport, TRANS_OPT_PUSH_CERT, "if-asked") != 0)
			die("helper %s does not support --signed=if-asked", name);
	}
}