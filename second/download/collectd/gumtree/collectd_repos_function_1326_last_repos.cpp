static grpc::Status marshal_meta_data(meta_data_t *meta,
                                      grpcMetadata *mutable_meta_data) {
  char **meta_data_keys = nullptr;
  int meta_data_keys_len = meta_data_toc(meta, &meta_data_keys);
  if (meta_data_keys_len < 0) {
    return grpc::Status(grpc::StatusCode::INTERNAL,
                        grpc::string("error getting metadata keys"));
  }

  for (int i = 0; i < meta_data_keys_len; i++) {
    char *key = meta_data_keys[i];
    int md_type = meta_data_type(meta, key);

    collectd::types::MetadataValue md_value;
    md_value.Clear();

    switch (md_type) {
    case MD_TYPE_STRING:
      char *md_string;
      if (meta_data_get_string(meta, key, &md_string) != 0 || md_string == nullptr) {
        strarray_free(meta_data_keys, meta_data_keys_len);
        return grpc::Status(grpc::StatusCode::INTERNAL,
                          grpc::string("missing metadata"));
      }
      md_value.set_string_value(md_string);
      free(md_string);
      break;
    case MD_TYPE_SIGNED_INT:
      int64_t int64_value;
      if (meta_data_get_signed_int(meta, key, &int64_value) != 0) {
        strarray_free(meta_data_keys, meta_data_keys_len);
        return grpc::Status(grpc::StatusCode::INTERNAL,
                          grpc::string("missing metadata"));
      }
      md_value.set_int64_value(int64_value);
      break;
    case MD_TYPE_UNSIGNED_INT:
      uint64_t uint64_value;
      if (meta_data_get_unsigned_int(meta, key, &uint64_value) != 0) {
        strarray_free(meta_data_keys, meta_data_keys_len);
        return grpc::Status(grpc::StatusCode::INTERNAL,
                          grpc::string("missing metadata"));
      }
      md_value.set_uint64_value(uint64_value);
      break;
    case MD_TYPE_DOUBLE:
      double double_value;
      if (meta_data_get_double(meta, key, &double_value) != 0) {
        strarray_free(meta_data_keys, meta_data_keys_len);
        return grpc::Status(grpc::StatusCode::INTERNAL,
                          grpc::string("missing metadata"));
      }
      md_value.set_double_value(double_value);
      break;
    case MD_TYPE_BOOLEAN:
      bool bool_value;
      if (meta_data_get_boolean(meta, key, &bool_value) != 0) {
        strarray_free(meta_data_keys, meta_data_keys_len);
        return grpc::Status(grpc::StatusCode::INTERNAL,
                          grpc::string("missing metadata"));
      }
      md_value.set_bool_value(bool_value);
      break;
    default:
      strarray_free(meta_data_keys, meta_data_keys_len);
      ERROR("grpc: invalid metadata type (%d)", md_type);
      return grpc::Status(grpc::StatusCode::INTERNAL,
                          grpc::string("unknown metadata type"));
    }

    (*mutable_meta_data)[grpc::string(key)] = md_value;

    strarray_free(meta_data_keys, meta_data_keys_len);
  }

  return grpc::Status::OK;
}