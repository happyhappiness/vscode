static _Bool camqp_is_error(camqp_config_t *conf) /* {{{ */
{
  amqp_rpc_reply_t r;

  r = amqp_get_rpc_reply(conf->connection);
  if (r.reply_type == AMQP_RESPONSE_NORMAL)
    return 0;

  return 1;
}