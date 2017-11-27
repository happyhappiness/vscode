static int varnish_read(user_data_t *ud) /* {{{ */
{
  const c_varnish_stats_t *stats;

  user_config_t *conf;

  if ((ud == NULL) || (ud->data == NULL))
    return EINVAL;

  conf = ud->data;

  stats = VSL_OpenStats(conf->instance);
  if (stats == NULL) {
    ERROR("Varnish plugin : unable to load statistics");

    return -1;
  }

  varnish_monitor(conf, stats);

  return 0;
}