int c_grpc_config_server(oconfig_item_t *ci)
	{
		if ((ci->values_num != 2)
				|| (ci->values[0].type != OCONFIG_TYPE_STRING)
				|| (ci->values[1].type != OCONFIG_TYPE_STRING)) {
			ERROR("grpc: The `%s` config option needs exactly "
					"two string argument (address and port).", ci->key);
			return -1;
		}

		grpc::SslCredentialsOptions ssl_opts;
		bool use_ssl = false;

		for (int i = 0; i < ci->children_num; i++) {
			oconfig_item_t *child = ci->children + i;

			if (!strcasecmp("EnableSSL", child->key)) {
				if (cf_util_get_boolean(child, &use_ssl)) {
					return -1;
				}
			}
			else if (!strcasecmp("SSLCACertificateFile", child->key)) {
				char *certs = NULL;
				if (cf_util_get_string(child, &certs)) {
					return -1;
				}
				ssl_opts.pem_root_certs = read_file(certs);
			}
			else if (!strcasecmp("SSLCertificateKeyFile", child->key)) {
				char *key = NULL;
				if (cf_util_get_string(child, &key)) {
					return -1;
				}
				ssl_opts.pem_private_key = read_file(key);
			}
			else if (!strcasecmp("SSLCertificateFile", child->key)) {
				char *cert = NULL;
				if (cf_util_get_string(child, &cert)) {
					return -1;
				}
				ssl_opts.pem_cert_chain = read_file(cert);
			}
			else {
				WARNING("grpc: Option `%s` not allowed in <%s> block.",
						child->key, ci->key);
			}
		}

		auto node    = grpc::string(ci->values[0].value.string);
		auto service = grpc::string(ci->values[1].value.string);
		auto addr    = node + ":" + service;

		CollectdClient *client;
		if (use_ssl) {
			auto channel_creds = grpc::SslCredentials(ssl_opts);
			auto channel = grpc::CreateChannel(addr, channel_creds);
			client = new CollectdClient(channel);
		} else {
			auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
			client = new CollectdClient(channel);
		}

		auto callback_name = grpc::string("grpc/") + addr;
		user_data_t ud = {
			.data = client,
			.free_func = c_grpc_destroy_write_callback,
		};

		plugin_register_write (callback_name.c_str(), c_grpc_write, &ud);
		return 0;
	}