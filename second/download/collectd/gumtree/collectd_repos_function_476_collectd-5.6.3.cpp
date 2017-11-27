static void free_nut_ups_t(nut_ups_t *ups) {
  if (ups->conn != NULL) {
    upscli_disconnect(ups->conn);
    sfree(ups->conn);
  }
  sfree(ups->hostname);
  sfree(ups->upsname);
  sfree(ups);
}