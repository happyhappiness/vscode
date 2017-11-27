void Start()
	{
		auto auth = grpc::InsecureServerCredentials();

		grpc::ServerBuilder builder;

		if (listeners.empty()) {
			builder.AddListeningPort(default_addr, auth);
			INFO("grpc: Listening on %s", default_addr.c_str());
		}
		else {
			for (auto l : listeners) {
				grpc::string addr = l.addr + ":" + l.port;

				auto use_ssl = grpc::string("");
				auto a = auth;
				if (l.ssl != nullptr) {
					use_ssl = grpc::string(" (SSL enabled)");
					a = grpc::SslServerCredentials(*l.ssl);
				}

				builder.AddListeningPort(addr, a);
				INFO("grpc: Listening on %s%s", addr.c_str(), use_ssl.c_str());
			}
		}

		builder.RegisterService(&collectd_service_);

		server_ = builder.BuildAndStart();
	}