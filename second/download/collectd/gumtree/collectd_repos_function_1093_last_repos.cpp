static int cgps_read(void) {
  cgps_data_t data_copy;

  pthread_mutex_lock(&cgps_data_lock);
  data_copy = cgps_data;
  pthread_mutex_unlock(&cgps_data_lock);

  cgps_submit("dilution_of_precision", data_copy.hdop, "horizontal");
  cgps_submit("dilution_of_precision", data_copy.vdop, "vertical");
  cgps_submit("satellites", data_copy.sats_used, "used");
  cgps_submit("satellites", data_copy.sats_visible, "visible");

  return 0;
}