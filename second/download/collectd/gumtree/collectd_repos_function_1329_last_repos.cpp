static grpc::Status unmarshal_value_list(const collectd::types::ValueList &msg,
                                         value_list_t *vl) {
  vl->time = NS_TO_CDTIME_T(TimeUtil::TimestampToNanoseconds(msg.time()));
  vl->interval =
      NS_TO_CDTIME_T(TimeUtil::DurationToNanoseconds(msg.interval()));

  auto status = unmarshal_ident(msg.identifier(), vl, true);
  if (!status.ok())
    return status;

  status = unmarshal_meta_data(msg.meta_data(), &vl->meta);
  if (!status.ok())
    return status;

  value_t *values = NULL;
  size_t values_len = 0;

  status = grpc::Status::OK;
  for (auto v : msg.values()) {
    value_t *val =
        (value_t *)realloc(values, (values_len + 1) * sizeof(*values));
    if (!val) {
      status = grpc::Status(grpc::StatusCode::RESOURCE_EXHAUSTED,
                            grpc::string("failed to allocate values array"));
      break;
    }

    values = val;
    val = values + values_len;
    values_len++;

    switch (v.value_case()) {
    case collectd::types::Value::ValueCase::kCounter:
      val->counter = counter_t(v.counter());
      break;
    case collectd::types::Value::ValueCase::kGauge:
      val->gauge = gauge_t(v.gauge());
      break;
    case collectd::types::Value::ValueCase::kDerive:
      val->derive = derive_t(v.derive());
      break;
    case collectd::types::Value::ValueCase::kAbsolute:
      val->absolute = absolute_t(v.absolute());
      break;
    default:
      status = grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            grpc::string("unknown value type"));
      break;
    }

    if (!status.ok())
      break;
  }
  if (status.ok()) {
    vl->values = values;
    vl->values_len = values_len;
  } else {
    meta_data_destroy(vl->meta);
    free(values);
  }

  return status;
}