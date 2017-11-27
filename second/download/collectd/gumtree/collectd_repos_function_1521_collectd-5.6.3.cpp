static int send_value(lcc_value_list_t *vl) /* {{{ */
{
  int status;

  if (vl->values_types[0] == LCC_TYPE_GAUGE)
    vl->values[0].gauge =
        100.0 * ((gauge_t)random()) / (((gauge_t)RAND_MAX) + 1.0);
  else
    vl->values[0].derive += (derive_t)get_boundet_random(0, 100);

  status = lcc_network_values_send(net, vl);
  if (status != 0)
    fprintf(stderr, "lcc_network_values_send failed with status %i.\n", status);

  vl->time += vl->interval;

  return (0);
}