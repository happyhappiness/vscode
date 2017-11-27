static grpc::Status marshal_value_list(const value_list_t *vl,
                                       collectd::types::ValueList *msg) {
  auto id = msg->mutable_identifier();
  marshal_ident(vl, id);

  auto ds = plugin_get_ds(vl->type);
  if ((ds == NULL) || (ds->ds_num != vl->values_len)) {
    return grpc::Status(grpc::StatusCode::INTERNAL,
                        grpc::string("failed to retrieve data-set for values"));
  }

  auto t = TimeUtil::NanosecondsToTimestamp(CDTIME_T_TO_NS(vl->time));
  auto d = TimeUtil::NanosecondsToDuration(CDTIME_T_TO_NS(vl->interval));
  msg->set_allocated_time(new google::protobuf::Timestamp(t));
  msg->set_allocated_interval(new google::protobuf::Duration(d));

  msg->clear_meta_data();
  if (vl->meta != nullptr) {
    grpc::Status status = marshal_meta_data(vl->meta, msg->mutable_meta_data());
    if (!status.ok()) {
      return status;
    }
  }

  for (size_t i = 0; i < vl->values_len; ++i) {
    auto v = msg->add_values();
    int value_type = ds->ds[i].type;
    switch (value_type) {
    case DS_TYPE_COUNTER:
      v->set_counter(vl->values[i].counter);
      break;
    case DS_TYPE_GAUGE:
      v->set_gauge(vl->values[i].gauge);
      break;
    case DS_TYPE_DERIVE:
      v->set_derive(vl->values[i].derive);
      break;
    case DS_TYPE_ABSOLUTE:
      v->set_absolute(vl->values[i].absolute);
      break;
    default:
      ERROR("grpc: invalid value type (%d)", value_type);
      return grpc::Status(grpc::StatusCode::INTERNAL,
                          grpc::string("unknown value type"));
    }

    auto name = msg->add_ds_names();
    name->assign(ds->ds[i].name);
  }

  return grpc::Status::OK;
}