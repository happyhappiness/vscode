static void free_nut_ups_t(void *arg) {
  nut_ups_t *ups = arg;

  if (ups->conn != NULL) {
    upscli_disconnect(ups->conn);
    sfree(ups->conn);
  }
  sfree(ups->hostname);
  sfree(ups->upsname);
  sfree(ups);
}