static int rc_shutdown(void) {
  rrdc_disconnect();
  return (0);
}