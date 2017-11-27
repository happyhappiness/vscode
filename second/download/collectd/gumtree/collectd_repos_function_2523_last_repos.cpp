static int network_parse(void *data, size_t data_size, lcc_security_level_t sl,
                         lcc_network_parse_options_t const *opts) {
  buffer_t *b = &(buffer_t){
      .data = data, .len = data_size,
  };

  lcc_value_list_t state = {0};

  while (b->len > 0) {
    uint16_t type = 0, sz = 0;
    if (buffer_uint16(b, &type) || buffer_uint16(b, &sz)) {
      DEBUG("lcc_network_parse(): reading type and/or length failed.\n");
      return EINVAL;
    }

    if ((sz < 5) || (((size_t)sz - 4) > b->len)) {
      DEBUG("lcc_network_parse(): invalid 'sz' field: sz = %" PRIu16
            ", b->len = %zu\n",
            sz, b->len);
      return EINVAL;
    }
    sz -= 4;

    uint8_t payload[sz];
    if (buffer_next(b, payload, sizeof(payload)))
      return EINVAL;

    switch (type) {
    case TYPE_HOST:
    case TYPE_PLUGIN:
    case TYPE_PLUGIN_INSTANCE:
    case TYPE_TYPE:
    case TYPE_TYPE_INSTANCE: {
      if (parse_identifier(type, payload, sizeof(payload), &state)) {
        DEBUG("lcc_network_parse(): parse_identifier failed.\n");
        return EINVAL;
      }
      break;
    }

    case TYPE_INTERVAL:
    case TYPE_INTERVAL_HR:
    case TYPE_TIME:
    case TYPE_TIME_HR: {
      if (parse_time(type, payload, sizeof(payload), &state)) {
        DEBUG("lcc_network_parse(): parse_time failed.\n");
        return EINVAL;
      }
      break;
    }

    case TYPE_VALUES: {
      lcc_value_list_t vl = state;
      if (parse_values(payload, sizeof(payload), &vl)) {
        free(vl.values);
        free(vl.values_types);
        DEBUG("lcc_network_parse(): parse_values failed.\n");
        return EINVAL;
      }

      int status = 0;

      /* Write metrics if they have the required security level. */
      if (sl >= opts->security_level)
        status = opts->writer(&vl);

      free(vl.values);
      free(vl.values_types);

      if (status != 0)
        return status;
      break;
    }

    case TYPE_SIGN_SHA256: {
      int status =
          parse_sign_sha256(payload, sizeof(payload), b->data, b->len, opts);
      if (status != 0) {
        DEBUG("lcc_network_parse(): parse_sign_sha256() = %d\n", status);
        return -1;
      }
      /* parse_sign_sha256, if successful, consumes all remaining data. */
      b->data = NULL;
      b->len = 0;
      break;
    }

    case TYPE_ENCR_AES256: {
      int status = parse_encrypt_aes256(payload, sizeof(payload), opts);
      if (status != 0) {
        DEBUG("lcc_network_parse(): parse_encrypt_aes256() = %d\n", status);
        return -1;
      }
      break;
    }

    default: {
      DEBUG("lcc_network_parse(): ignoring unknown type %" PRIu16 "\n", type);
      return EINVAL;
    }
    }
  }

  return 0;
}