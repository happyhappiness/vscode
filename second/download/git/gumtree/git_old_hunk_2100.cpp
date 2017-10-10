	if (server_supports("quiet"))
		quiet_supported = 1;
	if (server_supports("agent"))
		agent_supported = 1;
	if (server_supports("no-thin"))
		args->use_thin_pack = 0;
	if (args->push_cert) {
		int len;

		push_cert_nonce = server_feature_value("push-cert", &len);
		if (!push_cert_nonce)
			die(_("the receiving end does not support --signed push"));
