static void openvpn_free(void *arg) {
  vpn_status_t *st = arg;

  sfree(st->file);
  sfree(st);
}