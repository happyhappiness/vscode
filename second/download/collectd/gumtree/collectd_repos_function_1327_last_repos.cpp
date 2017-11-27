static grpc::Status unmarshal_meta_data(const grpcMetadata &rpc_metadata,
                                        meta_data_t **md_out) {
  *md_out = meta_data_create();
  if (*md_out == nullptr) {
    return grpc::Status(grpc::StatusCode::RESOURCE_EXHAUSTED,
                        grpc::string("failed to metadata list"));
  }
  for (auto kv: rpc_metadata) {
    auto k = kv.first.c_str();
    auto v = kv.second;

    // The meta_data collection individually allocates copies of the keys and
    // string values for each entry, so it's safe for us to pass a reference
    // to our short-lived strings.

    switch (v.value_case()) {
    case collectd::types::MetadataValue::ValueCase::kStringValue:
      meta_data_add_string(*md_out, k, v.string_value().c_str());
      break;
    case collectd::types::MetadataValue::ValueCase::kInt64Value:
      meta_data_add_signed_int(*md_out, k, v.int64_value());
      break;
    case collectd::types::MetadataValue::ValueCase::kUint64Value:
      meta_data_add_unsigned_int(*md_out, k, v.uint64_value());
      break;
    case collectd::types::MetadataValue::ValueCase::kDoubleValue:
      meta_data_add_double(*md_out, k, v.double_value());
      break;
    case collectd::types::MetadataValue::ValueCase::kBoolValue:
      meta_data_add_boolean(*md_out, k, v.bool_value());
      break;
    default:
      meta_data_destroy(*md_out);
      return  grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                           grpc::string("Metadata of unknown type"));
    }
  }
  return grpc::Status::OK;
}