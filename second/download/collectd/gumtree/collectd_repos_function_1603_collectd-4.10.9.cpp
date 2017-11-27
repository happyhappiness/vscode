static void submit_interface (cr_data_t *rd, /* {{{ */
    const ros_interface_t *i)
{
  if (i == NULL)
    return;

  if (!i->running)
  {
    submit_interface (rd, i->next);
    return;
  }

  cr_submit_io (rd, "if_packets", i->name,
      (counter_t) i->rx_packets, (counter_t) i->tx_packets);
  cr_submit_io (rd, "if_octets", i->name,
      (counter_t) i->rx_bytes, (counter_t) i->tx_bytes);
  cr_submit_io (rd, "if_errors", i->name,
      (counter_t) i->rx_errors, (counter_t) i->tx_errors);
  cr_submit_io (rd, "if_dropped", i->name,
      (counter_t) i->rx_drops, (counter_t) i->tx_drops);

  submit_interface (rd, i->next);
}