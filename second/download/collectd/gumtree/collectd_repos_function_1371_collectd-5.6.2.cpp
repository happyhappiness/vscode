static int mc_handle_value_msg(Ganglia_value_msg *msg) /* {{{ */
{
  const char *host;
  const char *name;
  metric_map_t *map;

  value_t value_counter;
  value_t value_gauge;
  value_t value_derive;

  /* Fill in `host', `name', `value_counter', and `value_gauge' according to
   * the value type, or return with an error. */
  switch (msg->id) /* {{{ */
  {
  case gmetric_uint: {
    Ganglia_gmetric_uint msg_uint;

    msg_uint = msg->Ganglia_value_msg_u.gu_int;

    host = msg_uint.metric_id.host;
    name = msg_uint.metric_id.name;
    value_counter.counter = (counter_t)msg_uint.ui;
    value_gauge.gauge = (gauge_t)msg_uint.ui;
    value_derive.derive = (derive_t)msg_uint.ui;
    break;
  }

  case gmetric_string: {
    Ganglia_gmetric_string msg_string;
    int status;

    msg_string = msg->Ganglia_value_msg_u.gstr;

    host = msg_string.metric_id.host;
    name = msg_string.metric_id.name;

    status = parse_value(msg_string.str, &value_derive, DS_TYPE_DERIVE);
    if (status != 0)
      value_derive.derive = -1;

    status = parse_value(msg_string.str, &value_gauge, DS_TYPE_GAUGE);
    if (status != 0)
      value_gauge.gauge = NAN;

    status = parse_value(msg_string.str, &value_counter, DS_TYPE_COUNTER);
    if (status != 0)
      value_counter.counter = 0;

    break;
  }

  case gmetric_float: {
    Ganglia_gmetric_float msg_float;

    msg_float = msg->Ganglia_value_msg_u.gf;

    host = msg_float.metric_id.host;
    name = msg_float.metric_id.name;
    value_counter.counter = (counter_t)msg_float.f;
    value_gauge.gauge = (gauge_t)msg_float.f;
    value_derive.derive = (derive_t)msg_float.f;
    break;
  }

  case gmetric_double: {
    Ganglia_gmetric_double msg_double;

    msg_double = msg->Ganglia_value_msg_u.gd;

    host = msg_double.metric_id.host;
    name = msg_double.metric_id.name;
    value_counter.counter = (counter_t)msg_double.d;
    value_gauge.gauge = (gauge_t)msg_double.d;
    value_derive.derive = (derive_t)msg_double.d;
    break;
  }
  default:
    DEBUG("gmond plugin: Value type not handled: %i", msg->id);
    return (-1);
  } /* }}} switch (msg->id) */

  assert(host != NULL);
  assert(name != NULL);

  map = metric_lookup(name);
  if (map != NULL) {
    value_t val_copy;

    if ((map->ds_type == DS_TYPE_COUNTER) || (map->ds_type == DS_TYPE_ABSOLUTE))
      val_copy = value_counter;
    else if (map->ds_type == DS_TYPE_GAUGE)
      val_copy = value_gauge;
    else if (map->ds_type == DS_TYPE_DERIVE)
      val_copy = value_derive;
    else
      assert(23 == 42);

    return (staging_entry_update(host, name, map->type, map->type_instance,
                                 map->ds_index, map->ds_type, val_copy));
  }

  DEBUG("gmond plugin: Cannot find a translation for %s.", name);
  return (-1);
}