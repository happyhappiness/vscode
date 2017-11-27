grpc::Status DispatchValues(grpc::ServerContext *ctx,
								grpc::ServerReader<DispatchValuesRequest> *reader,
								DispatchValuesResponse *res) override {
		DispatchValuesRequest req;

		while (reader->Read(&req)) {
			value_list_t vl = VALUE_LIST_INIT;
			auto status = unmarshal_value_list(req.value_list(), &vl);
			if (!status.ok())
				return status;

			if (plugin_dispatch_values(&vl))
				return grpc::Status(grpc::StatusCode::INTERNAL,
									grpc::string("failed to enqueue values for writing"));
		}

		res->Clear();
		return grpc::Status::OK;
	}