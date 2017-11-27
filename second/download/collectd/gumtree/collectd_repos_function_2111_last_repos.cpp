static int mb_config_add_data(oconfig_item_t *ci) /* {{{ */
{
  mb_data_t data = {0};
  int status;

  data.name = NULL;
  data.register_type = REG_TYPE_UINT16;
  data.next = NULL;

  status = cf_util_get_string(ci, &data.name);
  if (status != 0)
    return status;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Type", child->key) == 0)
      status = cf_util_get_string_buffer(child, data.type, sizeof(data.type));
    else if (strcasecmp("Instance", child->key) == 0)
      status = cf_util_get_string_buffer(child, data.instance,
                                         sizeof(data.instance));
    else if (strcasecmp("RegisterBase", child->key) == 0)
      status = cf_util_get_int(child, &data.register_base);
    else if (strcasecmp("RegisterType", child->key) == 0) {
      char tmp[16];
      status = cf_util_get_string_buffer(child, tmp, sizeof(tmp));
      if (status != 0)
        /* do nothing */;
      else if (strcasecmp("Int16", tmp) == 0)
        data.register_type = REG_TYPE_INT16;
      else if (strcasecmp("Int32", tmp) == 0)
        data.register_type = REG_TYPE_INT32;
      else if (strcasecmp("Uint16", tmp) == 0)
        data.register_type = REG_TYPE_UINT16;
      else if (strcasecmp("Uint32", tmp) == 0)
        data.register_type = REG_TYPE_UINT32;
      else if (strcasecmp("Float", tmp) == 0)
        data.register_type = REG_TYPE_FLOAT;
      else {
        ERROR("Modbus plugin: The register type \"%s\" is unknown.", tmp);
        status = -1;
      }
    } else if (strcasecmp("RegisterCmd", child->key) == 0) {
#if LEGACY_LIBMODBUS
      ERROR("Modbus plugin: RegisterCmd parameter can not be used "
            "with your libmodbus version");
#else
      char tmp[16];
      status = cf_util_get_string_buffer(child, tmp, sizeof(tmp));
      if (status != 0)
        /* do nothing */;
      else if (strcasecmp("ReadHolding", tmp) == 0)
        data.modbus_register_type = MREG_HOLDING;
      else if (strcasecmp("ReadInput", tmp) == 0)
        data.modbus_register_type = MREG_INPUT;
      else {
        ERROR("Modbus plugin: The modbus_register_type \"%s\" is unknown.",
              tmp);
        status = -1;
      }
#endif
    } else {
      ERROR("Modbus plugin: Unknown configuration option: %s", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  assert(data.name != NULL);
  if (data.type[0] == 0) {
    ERROR("Modbus plugin: Data block \"%s\": No type has been specified.",
          data.name);
    status = -1;
  }

  if (status == 0)
    data_copy(&data_definitions, &data);

  sfree(data.name);

  return status;
}