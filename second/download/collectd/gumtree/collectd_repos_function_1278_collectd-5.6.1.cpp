grpc::Status QueryValues(grpc::ServerContext *ctx, QueryValuesRequest const *req, grpc::ServerWriter<QueryValuesResponse> *writer) override {
		value_list_t match;
		auto status = unmarshal_ident(req->identifier(), &match, false);
		if (!status.ok()) {
			return status;
		}

		std::queue<value_list_t> value_lists;
		status = this->queryValuesRead(&match, &value_lists);
		if (status.ok()) {
			status = this->queryValuesWrite(ctx, writer, &value_lists);
		}

		while (!value_lists.empty()) {
			auto vl = value_lists.front();
			value_lists.pop();
			sfree(vl.values);
		}

		return status;
	}