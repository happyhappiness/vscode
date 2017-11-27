static void submit_interface(cr_data_t *rd, /* {{{ */
                             const ros_interface_t *i) {
  if (i == NULL)
    return;

  if (!i->running) {
    submit_interface(rd, i->next);
    return;
  }

  cr_submit_io(rd, "if_packets", i->name, (derive_t)i->rx_packets,
               (derive_t)i->tx_packets);
  cr_submit_io(rd, "if_octets", i->name, (derive_t)i->rx_bytes,
               (derive_t)i->tx_bytes);
  cr_submit_io(rd, "if_errors", i->name, (derive_t)i->rx_errors,
               (derive_t)i->tx_errors);
  cr_submit_io(rd, "if_dropped", i->name, (derive_t)i->rx_drops,
               (derive_t)i->tx_drops);

  submit_interface(rd, i->next);
}