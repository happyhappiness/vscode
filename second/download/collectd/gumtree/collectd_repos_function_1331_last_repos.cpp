grpc::Status PutValues(grpc::ServerContext *ctx,
                         grpc::ServerReader<PutValuesRequest> *reader,
                         PutValuesResponse *res) override {
    PutValuesRequest req;

    while (reader->Read(&req)) {
      value_list_t vl = {0};
      auto status = unmarshal_value_list(req.value_list(), &vl);
      if (!status.ok())
        return status;

      if (plugin_dispatch_values(&vl))
        return grpc::Status(
            grpc::StatusCode::INTERNAL,
            grpc::string("failed to enqueue values for writing"));
    }

    res->Clear();
    return grpc::Status::OK;
  }