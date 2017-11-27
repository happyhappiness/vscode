static void submit_antx(const char *dev, const char *name, u_int32_t *vals,
                        int vals_num) {
  char ti2[16];

  for (int i = 0; i < vals_num; i++) {
    if (vals[i] == 0)
      continue;

    snprintf(ti2, sizeof(ti2), "%i", i);
    submit_derive(dev, "ath_stat", name, ti2, (derive_t)vals[i]);
  }
}