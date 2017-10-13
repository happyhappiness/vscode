static int send_pack_config(const char *k, const char *v, void *cb)
{
	git_gpg_config(k, v, NULL);

	if (!strcmp(k, "push.gpgsign")) {
		const char *value;
		if (!git_config_get_value("push.gpgsign", &value)) {
			switch (git_config_maybe_bool("push.gpgsign", value)) {
			case 0:
				args.push_cert = SEND_PACK_PUSH_CERT_NEVER;
				break;
			case 1:
				args.push_cert = SEND_PACK_PUSH_CERT_ALWAYS;
				break;
			default:
				if (value && !strcasecmp(value, "if-asked"))
					args.push_cert = SEND_PACK_PUSH_CERT_IF_ASKED;
				else
					return error("Invalid value for '%s'", k);
			}
		}
	}
	return 0;
}