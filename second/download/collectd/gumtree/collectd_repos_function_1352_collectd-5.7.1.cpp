int PutValues(value_list_t const *vl) {
		grpc::ClientContext ctx;

		PutValuesRequest req;
		auto status = marshal_value_list(vl, req.mutable_value_list());
		if (!status.ok()) {
			ERROR("grpc: Marshalling value_list_t failed.");
			return -1;
		}

		PutValuesResponse res;
		auto stream = stub_->PutValues(&ctx, &res);
		if (!stream->Write(req)) {
			NOTICE("grpc: Broken stream.");
			/* intentionally not returning. */
		}

		stream->WritesDone();
		status = stream->Finish();
		if (!status.ok()) {
			ERROR ("grpc: Error while closing stream.");
			return -1;
		}

		return 0;
	}