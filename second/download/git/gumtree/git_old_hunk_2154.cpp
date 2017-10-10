	if (args->push_cert) {
		int len;

		push_cert_nonce = server_feature_value("push-cert", &len);
		if (!push_cert_nonce)
			die(_("the receiving end does not support --signed push"));
		push_cert_nonce = xmemdupz(push_cert_nonce, len);
	}

	if (!remote_refs) {
		fprintf(stderr, "No refs in common and none specified; doing nothing.\n"
			"Perhaps you should specify a branch such as 'master'.\n");
