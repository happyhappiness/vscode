static int nut_verify_peer(const char *value) {
  if (strcasecmp(value, "true") == 0)
    verify_peer = 1;
  else if (strcasecmp(value, "false") == 0)
    verify_peer = 0; // Should already be set to 0 from initialization
  else {
    verify_peer = 0;
    WARNING("nut plugin: nut_verify_peer: invalid VERIFYPEER value "
            "found. Defaulting to false.");
  }
  return 0;
}