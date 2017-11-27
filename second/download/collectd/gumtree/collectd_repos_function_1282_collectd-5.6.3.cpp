grpc::Status queryValuesWrite(grpc::ServerContext *ctx,
					   grpc::ServerWriter<QueryValuesResponse> *writer,
					   std::queue<value_list_t> *value_lists) {
		while (!value_lists->empty()) {
			auto vl = value_lists->front();
			QueryValuesResponse res;
			res.Clear();

			auto status = marshal_value_list(&vl, res.mutable_value_list());
			if (!status.ok()) {
				return status;
			}

			if (!writer->Write(res)) {
				return grpc::Status::CANCELLED;
			}

			value_lists->pop();
			sfree(vl.values);
		}

		return grpc::Status::OK;
	}