static int c_grpc_config(oconfig_item_t *ci)
	{
		int i;

		for (i = 0; i < ci->children_num; i++) {
			oconfig_item_t *child = ci->children + i;

			if (!strcasecmp("Listen", child->key)) {
				if (c_grpc_config_listen(child))
					return -1;
			}
			else if (!strcasecmp("Server", child->key)) {
				if (c_grpc_config_server(child))
					return -1;
			}

			else {
				WARNING("grpc: Option `%s` not allowed here.", child->key);
			}
		}

		return 0;
	}