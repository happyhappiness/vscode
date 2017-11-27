static int camqp_create_exchange(camqp_config_t *conf) /* {{{ */
{
  amqp_exchange_declare_ok_t *ed_ret;
  amqp_table_t argument_table;
  struct amqp_table_entry_t_ argument_table_entries[1];

  if (conf->exchange_type == NULL)
    return (0);

  /* Valid arguments: "auto_delete", "internal" */
  argument_table.num_entries = STATIC_ARRAY_SIZE(argument_table_entries);
  argument_table.entries = argument_table_entries;
  argument_table_entries[0].key = amqp_cstring_bytes("auto_delete");
  argument_table_entries[0].value.kind = AMQP_FIELD_KIND_BOOLEAN;
  argument_table_entries[0].value.value.boolean = 1;

  ed_ret = amqp_exchange_declare(
      conf->connection,
      /* channel     = */ CAMQP_CHANNEL,
      /* exchange    = */ amqp_cstring_bytes(conf->exchange),
      /* type        = */ amqp_cstring_bytes(conf->exchange_type),
      /* passive     = */ 0,
      /* durable     = */ 0,
#if defined(AMQP_VERSION) && AMQP_VERSION >= 0x00060000
      /* auto delete = */ 0,
      /* internal    = */ 0,
#endif
      /* arguments   = */ argument_table);
  if ((ed_ret == NULL) && camqp_is_error(conf)) {
    char errbuf[1024];
    ERROR("amqp plugin: amqp_exchange_declare failed: %s",
          camqp_strerror(conf, errbuf, sizeof(errbuf)));
    camqp_close_connection(conf);
    return (-1);
  }

  INFO("amqp plugin: Successfully created exchange \"%s\" "
       "with type \"%s\".",
       conf->exchange, conf->exchange_type);

  return (0);
}