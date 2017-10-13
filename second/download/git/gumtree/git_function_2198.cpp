int option_parse_push_signed(const struct option *opt,
			     const char *arg, int unset)
{
	if (unset) {
		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_NEVER;
		return 0;
	}
	switch (git_parse_maybe_bool(arg)) {
	case 1:
		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_ALWAYS;
		return 0;
	case 0:
		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_NEVER;
		return 0;
	}
	if (!strcasecmp("if-asked", arg)) {
		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_IF_ASKED;
		return 0;
	}
	die("bad %s argument: %s", opt->long_name, arg);
}