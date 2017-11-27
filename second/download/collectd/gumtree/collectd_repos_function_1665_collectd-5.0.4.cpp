static void submit_regtable (cr_data_t *rd, /* {{{ */
    const ros_registration_table_t *r)
{
  char type_instance[DATA_MAX_NAME_LEN];

  if (r == NULL)
    return;

  /*** RX ***/
  ssnprintf (type_instance, sizeof (type_instance), "%s-%s-rx",
      r->interface, r->radio_name);
  cr_submit_gauge (rd, "bitrate", type_instance,
      (gauge_t) (1000000.0 * r->rx_rate));
  cr_submit_gauge (rd, "signal_power", type_instance,
      (gauge_t) r->rx_signal_strength);
  cr_submit_gauge (rd, "signal_quality", type_instance,
      (gauge_t) r->rx_ccq);

  /*** TX ***/
  ssnprintf (type_instance, sizeof (type_instance), "%s-%s-tx",
      r->interface, r->radio_name);
  cr_submit_gauge (rd, "bitrate", type_instance,
      (gauge_t) (1000000.0 * r->tx_rate));
  cr_submit_gauge (rd, "signal_power", type_instance,
      (gauge_t) r->tx_signal_strength);
  cr_submit_gauge (rd, "signal_quality", type_instance,
      (gauge_t) r->tx_ccq);

  /*** RX / TX ***/
  ssnprintf (type_instance, sizeof (type_instance), "%s-%s",
      r->interface, r->radio_name);
  cr_submit_io (rd, "if_octets", type_instance,
      (derive_t) r->rx_bytes, (derive_t) r->tx_bytes);
  cr_submit_gauge (rd, "snr", type_instance, (gauge_t) r->signal_to_noise);

  submit_regtable (rd, r->next);
}