static int nut_force_ssl(const char *value) {
  if (strcasecmp(value, "true") == 0)
    force_ssl = 1;
  else if (strcasecmp(value, "false") == 0)
    force_ssl = 0; // Should already be set to 0 from initialization
  else {
    force_ssl = 0;
    WARNING("nut plugin: nut_force_ssl: invalid FORCESSL value "
            "found. Defaulting to false.");
  }
  return 0;
}